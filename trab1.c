#include "edge_vector.h"
#include "vertex_vector.h"
#include "edge.h"
#include "vertex.h"
#include "union_find.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MSG(msg) fprintf(stderr, "%s\n", msg); exit(EXIT_FAILURE)

int process_line(char *line, VertexVector *vertex_vector, int aloc)
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

    vertex_vector_push_back(vertex_vector, name, coord);

    return aloc;
}

VertexVector *read_input(FILE *file, int *dimension, int k){
    VertexVector *vertex_vector = vertex_vector_init(10);
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

VertexVector *setup(char *directory, int *dimension, int k)
{
    FILE *file;
    file = fopen(directory, "r");

    if (file == NULL){
        ERROR_MSG("Arquivo de entradas não encontrado!\n");
    }

    VertexVector *vertex_vector = read_input(file, dimension, k);
    fclose(file);

    if (k < 1 || k > vertex_vector_size(vertex_vector))
    {
        vertex_vector_destroy(vertex_vector);
        ERROR_MSG("Valor de k inválido!\n");
    }

    return vertex_vector;
}

EdgeVector *calculate_distance(VertexVector *vertex_vector, int dimension)
{
    int size_vv = vertex_vector_size(vertex_vector);
    int size_ev = (size_vv * (size_vv - 1)) / 2;
    EdgeVector *edge_vector = edge_vector_init(size_ev);

    for (int i = 0; i < size_vv - 1; i++)
    {
        for (int j = i + 1; j < size_vv; j++)
        {
            Vertex *vertex1 = vertex_vector_get(vertex_vector, i);
            Vertex *vertex2 = vertex_vector_get(vertex_vector, j);
            double weight = vertex_distance_between(vertex1, vertex2, dimension);

            edge_vector_push_back(edge_vector, i, j, weight);
        }
    }

    return edge_vector;
}

UF *kruskal(EdgeVector *edge_vector, VertexVector *vertex_vector, int k)
{
    int size_v = vertex_vector_size(vertex_vector);
    int size_e = edge_vector_size(edge_vector);

    UF *uf = uf_init(size_v);
    edge_vector_sort(edge_vector);

    int i = 0;
    int j = 0;
    
    while (i < size_e && j < size_v - k) // (size_v -1) - (k - 1) = size_v - k
    {
        Edge edge = *edge_vector_get(edge_vector, i);
        int vertex1 = edge_get_vertex1(&edge);
        int vertex2 = edge_get_vertex2(&edge);

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
        return strcmp(vertex_get_id(vector_get(va, 0)), vertex_get_id(vector_get(vb, 0)));

    if (va == NULL && vb == NULL)
        return 0;

    if (va == NULL)
        return -1;

    return 1;
}

Vector **group_vertices(VertexVector *vertex_vector, UF *mst)
{
    int size = vertex_vector_size(vertex_vector);
    Vector **group_vector = (Vector **)calloc(size, sizeof(Vector *));

    for (int i = 0; i < size; i++)
    {
        int group = uf_find(mst, i);
        if (group_vector[group] == NULL)
            group_vector[group] = vector_init(10, NULL, group_compare);
        vector_push_back(group_vector[group], vertex_vector_get(vertex_vector, i));
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
                fprintf(file, "%s", vertex_get_id(vector_get(group_vector[i], j)));
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

void output(VertexVector *vertex_vector, UF *mst, int k, char *output_file)
{
    Vector **group_vector = group_vertices(vertex_vector, mst);
    sort_group(group_vector, vertex_vector_size(vertex_vector));
    print_group(group_vector, vertex_vector_size(vertex_vector), output_file);
    free_group(group_vector, vertex_vector_size(vertex_vector));
}

int main(int argc, char **argv)
{
    if (argc < 4)
        return 1;

    int k = atoi(argv[2]);
    int dimension = 0;

    VertexVector *vertex_vector = setup(argv[1], &dimension, k);
    printf("Setup\n");
    EdgeVector *edge_vector = calculate_distance(vertex_vector, dimension);
    printf("Calculate\n");
    UF *mst = kruskal(edge_vector, vertex_vector, k);
    printf("Kruskal\n");
    edge_vector_destroy(edge_vector);
    printf("Destroy 1\n");
    output(vertex_vector, mst, k, argv[3]);
    printf("Output\n");
    uf_destroy(mst);
    vertex_vector_destroy(vertex_vector);
    printf("Destroy 2\n");
    return 0;
}
