#include "vector.h"
#include "edge.h"
#include "vertex.h"
#include "union_find.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ERROR_MSG(msg) fprintf(stderr, msg); exit(EXIT_FAILURE)


int process_line(char *line, Vector *vertex_vector, int aloc)
{
    int n = 0;
    char *name = strtok(line, ",");
    char *token = strtok(NULL, ",");

    if (token == NULL){
        ERROR_MSG("Erro ao processar linha!\n");
    }

    double *coord = (double *)malloc((aloc + 1) * sizeof(double));

    while (token)
    {
        coord[n] = atof(token);

        if (n == aloc)
        {
            aloc++;
            coord = (double *)realloc(coord, (aloc + 1) * sizeof(double));
        }

        n++;
        token = strtok(NULL, ",");
    }

    Vertex *v = vertex_init(name, coord);
    vector_push_back(vertex_vector, v);

    return aloc;
}

Vector *read_input(FILE *file, int *dimension, int k){
    Vector *vertex_vector = vector_init(10, vertex_destroy, NULL);
    char *line = NULL;
    size_t size = 0;
    int len;
    int aloc = 2;

    if ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        aloc = process_line(line, vertex_vector, aloc);
    }

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        aloc = process_line(line, vertex_vector, aloc);
    }

    *dimension = aloc;

    free(line);
    return vertex_vector;
}

Vector *setup(char *directory, int *dimension, int k)
{
    FILE *file;
    file = fopen(directory, "r");

    if (file == NULL){
        ERROR_MSG("Arquivo de entradas não encontrado!\n");
    }

    Vector *vertex_vector = read_input(file, dimension, k);
    fclose(file);

    if (k < 1 || k > vector_size(vertex_vector))
    {
        vector_destroy(vertex_vector);
        ERROR_MSG("Valor de k inválido!\n");
    }

    return vertex_vector;
}

Vector *calculate_distance(Vector *vertex_vector, int dimension)
{
    int size_vv = vector_size(vertex_vector);
    int size_ev = (size_vv * (size_vv - 1)) / 2;
    Vector *edge_vector = vector_init(size_ev, edge_destroy, edge_compare);

    for (int i = 0; i < size_vv - 1; i++)
    {
        for (int j = i + 1; j < size_vv; j++)
        {
            Vertex *vertex1 = vector_get(vertex_vector, i);
            Vertex *vertex2 = vector_get(vertex_vector, j);
            double weight = vertex_distance_between(vertex1, vertex2, dimension);

            Edge *edge = edge_init(i, j, weight);
            vector_push_back(edge_vector, edge);
        }
    }

    return edge_vector;
}

UF *kruskal(Vector *edge_vector, Vector *vertex_vector, int k)
{
    int size_v = vector_size(vertex_vector);
    int size_e = vector_size(edge_vector);

    UF *uf = uf_init(size_v);
    vector_sort(edge_vector);

    int i = 0;
    int j = 0;
    
    while (i < size_e && j < size_v - k) // (size_v -1) - (k - 1) = size_v - k
    {
        Edge *edge = vector_get(edge_vector, i);
        int vertex1 = edge_get_vertex1(edge);
        int vertex2 = edge_get_vertex2(edge);

        if (uf_find(uf, vertex1) != uf_find(uf, vertex2))
        {
            uf_union(uf, vertex1, vertex2);
            j++;
        }
        i++;
    }
    return uf;
}

int group_compare(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

int group_vector_compare(const void *a, const void *b)
{
    Vector *va = *(Vector **)a;
    Vector *vb = *(Vector **)b;
    if (va && vb)
        return strcmp(vector_get(va, 0), vector_get(vb, 0));

    if (va == NULL && vb == NULL)
        return 0;

    if (va == NULL)
        return -1;

    return 1;
}

Vector **group_vertices(Vector *vertex_vector, UF *mst)
{
    int size = vector_size(vertex_vector);
    Vector **group_vector = (Vector **)calloc(size, sizeof(Vector *));

    for (int i = 0; i < size; i++)
    {
        int group = uf_find(mst, i);
        if (group_vector[group] == NULL)
            group_vector[group] = vector_init(10, NULL, group_compare);
        vector_push_back(group_vector[group], vertex_get_id(vector_get(vertex_vector, i)));
    }

    return group_vector;
}

void sort_group(Vector **group_vector, int size)
{
    for (int i = 0; i < size; i++)
        if (group_vector[i])
            vector_sort(group_vector[i]);
    qsort(group_vector, size, sizeof(Vector *), group_vector_compare);
}

void print_group(Vector **group_vector, int size, char *output_file)
{
    FILE *file = fopen(output_file, "w");
    if (file == NULL)
    {
        ERROR_MSG("Erro ao abrir arquivo de saída!\n");
    }

    for (int i = 0; i < size; i++)
    {
        if (group_vector[i] != NULL)
        {
            int g_size = vector_size(group_vector[i]);
            for (int j = 0; j < g_size; j++)
            {
                fprintf(file, "%s", (char *)vector_get(group_vector[i], j));
                if (j < g_size - 1)
                    fprintf(file, ",");
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
}


void free_group(Vector **group_vector, int size)
{
    for (int i = 0; i < size; i++)
        if (group_vector[i] != NULL)
            vector_destroy(group_vector[i]);
    free(group_vector);
}

void output(Vector *vertex_vector, UF *mst, int k, char *output_file)
{
    Vector **group_vector = group_vertices(vertex_vector, mst);
    sort_group(group_vector, vector_size(vertex_vector));
    print_group(group_vector, vector_size(vertex_vector), output_file);
    free_group(group_vector, vector_size(vertex_vector));
}

int main(int argc, char **argv)
{
    if (argc < 4)
        return 1;

    int k = atoi(argv[2]);
    int dimension = 0;

    Vector *vertex_vector = setup(argv[1], &dimension, k);
    printf("Setup\n");
    Vector *edge_vector = calculate_distance(vertex_vector, dimension);
    printf("Calculate\n");
    UF *mst = kruskal(edge_vector, vertex_vector, k);
    printf("Kruskal\n");
    vector_destroy(edge_vector);
    printf("Destroy 1\n");
    output(vertex_vector, mst, k, argv[3]);
    printf("Output\n");
    uf_destroy(mst);
    vector_destroy(vertex_vector);
    printf("Destroy 2\n");
    return 0;
}