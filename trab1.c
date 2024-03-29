#include "vector.h"
#include "edge.h"
#include "vertex.h"
#include "union_find.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setup(char *directory, Vector *vertex_vector, int *dimension)
{
    FILE *file;
    file = fopen(directory, "r");

    if (file == NULL)
        exit(printf("Arquivo de entradas não encontrado!\nNome: %s\n", directory));

    char *line = NULL;
    size_t size = 0;
    int len, n = 0;

    while ((len = getline(&line, &size, file)) != -1)
    {

        line[len - 1] = '\0';

        char *name = strtok(line, ",");
        char *token = strtok(NULL, ",");

        if (token == NULL)
        {
            exit(printf("Arquivo de entradas invalido!\n"));
        }

        n = 0;
        int aloc_init = 2;
        double *coord = (double *)malloc(aloc_init * sizeof(double));

        while (token)
        {
            coord[n] = atof(token);
            n++;

            if (n == aloc_init - 1)
            {
                aloc_init *= 2;
                coord = (double *)realloc(coord, aloc_init * sizeof(double));
            }

            token = strtok(NULL, ",");
        }

        Vertex *v = vertex_init(name, coord);
        vector_push_back(vertex_vector, v);
    }
    *dimension = n;
    free(line);
    fclose(file);
}

void calculate_distance(Vector *edge_vector, Vector *vertex_vector, int dimension)
{
    int size_vv = vector_size(vertex_vector);
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
}

// void print_teste(Vector *v, int d)
// {
//     int i = 0;
//     int size_v = vector_size(v);
//     while(i < size_v){

//         Vertex * vex = vector_get(v, i);
//         vertex_print(vex, d);
//         i++;
//     }
// }

// isso aqui retorna uma quase mst, mais especificamente um union find com os grupos que a gente tem que retornar na resposta
// entao o próximo passo é encontrar cada grupo formado pelo union find. Esses prints ajudam muito a entender o que está acontecendo
// to pensando em usar um vetor de listas encadeadas para definir os grupos. esse vetor tem tamanho k (grupos) e cada posição é uma lista encadeada
// a medida que percorre o union find verifica qual é a raiz, ou seja, a qual dos k grupos ele pertence e adiciona à lista encadeada do grupo respectivo
// criar uma função pra isso
UF *kruskal(Vector *edge_vector, Vector *vertex_vector, int k)
{
    int size_v = vector_size(vertex_vector);
    int size_e = vector_size(edge_vector);

    UF *uf = uf_init(size_v);
    vector_sort(edge_vector);

    int i = 0;
    int j = 0;

    while (i < size_e && j < size_v - k)
    { // size_v - 1 arestas para formar a arvore minima
        Edge *edge = vector_get(edge_vector, i);
        int vertex1 = edge_get_vertex1(edge);
        int vertex2 = edge_get_vertex2(edge);

        if (uf_find(uf, vertex1) != uf_find(uf, vertex2))
        {
            uf_union(uf, vertex1, vertex2);
            //printf("%s[%d] %s[%d]\n", vertex_get_id(vector_get(vertex_vector, vertex1)), vertex1, vertex_get_id(vector_get(vertex_vector, vertex2)), vertex2); 
            //print_uf(uf);
            j++;
        }
        i++;
    }
    return uf;
}

int main(int argc, char **argv)
{

    if (argc < 4)
    {
        // TODO : tem que colocar em algum lugar todas as verificações necessarias para encerrar o programa em caso de entrada errada
        // exemplos, valor de k > numero de vertices. arquivo de entrada nao existente, erro ao salvar o arquivo (sei lá, o professor colocou uma pasta que nao existe)
        // formato de entrada: ./trab1 entrada k saida
        return 1;
    }
    int *dimension = (int *)malloc(sizeof(int));
    int k = atoi(argv[2]); // TODO : verificar se é nulo

    Vector *vertex_vector = vector_init(10, vertex_destroy, NULL);
    setup(argv[1], vertex_vector, dimension);

    // printf("%d\n", *dimension);
    // print_teste(vertex_vector, *dimension);

    int n_edges = vector_size(vertex_vector) - 1;
    Vector *edge_vector = vector_init(n_edges, edge_destroy, edge_compare);
    calculate_distance(edge_vector, vertex_vector, *dimension);

    UF *mst = kruskal(edge_vector, vertex_vector, k);
    // for(int i = 0; i < vector_size(edge_vector); i++){
    //     Edge* ed = vector_get(edge_vector, i);
    //     Vertex *v1 = vector_get(vertex_vector,edge_get_vertex1(ed));
    //     Vertex *v2 = vector_get(vertex_vector, edge_get_vertex2(ed));
    //     double weight = edge_get_weight(ed);
    //     printf("%lf \t %s[%d]  %s[%d]\n",weight, vertex_get_id(v1), edge_get_vertex1(ed), vertex_get_id(v2), edge_get_vertex2(ed));
    // }
    

    uf_destroy(mst);
    vector_destroy(vertex_vector);
    vector_destroy(edge_vector);
    free(dimension);

    // ordenar
    // calcular a arvore minima
    // remover k ultimos
    // salvar resultado
    return 0;
}