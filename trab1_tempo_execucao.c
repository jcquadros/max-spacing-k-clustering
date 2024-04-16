#include "edge_vector.h"
#include "vertex_vector.h"
#include "edge.h"
#include "vertex.h"
#include "union_find.h"
#include "io.h"
#include <stdlib.h>
#include <time.h>
#include<stdio.h>

/*
 * setup
 * -----
 * Configura o ambiente de execução lendo o arquivo de entrada, ordenando os vértices
 * e verificando a validade do número de grupos desejados.
 *
 * Parâmetros:
 *   - directory: o diretório do arquivo de entrada.
 *   - dimension: ponteiro para armazenar a dimensão do espaço (R^n).
 *   - k: o número de grupos desejados.
 *
 * Retorno:
 *   - Um ponteiro para o vetor de vértices lido do arquivo de entrada.
 */
VertexVector *setup(char *directory, int *dimension, int k)
{
    VertexVector *vertex_vector = read_input(directory, dimension);
    vertex_vector_sort(vertex_vector);

    if (k < 1 || k > vertex_vector_size(vertex_vector))
    {
        vertex_vector_destroy(vertex_vector);
        exit(1);
    }

    return vertex_vector;
}

/*
 * calculate_distance
 * ------------------
 * Calcula as distâncias entre todos os pares de vértices e armazena as arestas em um vetor.
 *
 * Parâmetros:
 *   - vertex_vector: o vetor de vértices.
 *   - dimension: a dimensão do espaço (R^n).
 *
 * Retorno:
 *   - Um ponteiro para o vetor de arestas contendo todas as distâncias calculadas.
 */
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
    edge_vector_sort(edge_vector);
    return edge_vector;
}

/*
 * kruskal
 * -------
 * Algoritmo de Kruskal para encontrar a "quase" Árvore Geradora Mínima (quase-MST).
 * A função para de gerar a arvore quando o número de grupos desejados é atingido.
 *
 * Parâmetros:
 *   - edge_vector: o vetor de arestas contendo as distâncias entre os vértices.
 *   - vertex_vector: o vetor de vértices.
 *   - k: o número de grupos desejados.
 *
 * Retorno:
 *   - Um ponteiro para a estrutura Union-Find representando a quase-MST.
 */
UF *kruskal(EdgeVector *edge_vector, VertexVector *vertex_vector, int k)
{
    int size_v = vertex_vector_size(vertex_vector);
    int size_e = edge_vector_size(edge_vector);

    UF *mst = uf_init(size_v);

    int i = 0;
    int j = 0;

    while (i < size_e && j < size_v - k) // (size_v -1) - (k - 1) = size_v - k
    {
        Edge edge = *edge_vector_get(edge_vector, i);
        int vertex1 = edge_get_vertex1(&edge);
        int vertex2 = edge_get_vertex2(&edge);

        if (uf_find(mst, vertex1) != uf_find(mst, vertex2))
        {
            uf_union(mst, vertex1, vertex2);
            j++;
        }
        i++;
    }
    return mst;
}

/*
 * main
 * ----
 * Lê os argumentos da linha de comando, configura o ambiente,
 * executa o algoritmo de Kruskal e escreve o resultado no arquivo de saída.
 */
int main(int argc, char **argv)
{
    clock_t start, stop, start_full, stop_full;
    start_full = clock();
    if (argc < 4)
        return 1;

    int k = atoi(argv[2]);
    int dimension = 0;
    start = clock();
    VertexVector *vertex_vector = setup(argv[1], &dimension, k);
    stop = clock();
    double time_taken_setup = ((double)stop - start)/ CLOCKS_PER_SEC;

    start = clock();
    EdgeVector *edge_vector = calculate_distance(vertex_vector, dimension);
    stop = clock();
    double time_taken_calculate_distance = ((double)stop - start)/ CLOCKS_PER_SEC;

    start = clock();
    UF *uf = kruskal(edge_vector, vertex_vector, k);
    stop = clock();
    double time_taken_kruskal = ((double)stop - start)/ CLOCKS_PER_SEC;

    edge_vector_destroy(edge_vector);

    start = clock();
    write_output(vertex_vector, uf, argv[3]);
    stop = clock();
    double time_taken_output = ((double)stop - start)/ CLOCKS_PER_SEC;

    uf_destroy(uf);
    vertex_vector_destroy(vertex_vector);

    stop_full = clock();
    double time_taken_total = ((double)stop_full - start_full)/ CLOCKS_PER_SEC;

    printf("total: %.5f\n", time_taken_total);
    printf("setup: %.5f\n", time_taken_setup);
    printf("distance: %.5f\n", time_taken_calculate_distance);
    printf("kruskal: %.5f\n", time_taken_kruskal);
    printf("output: %.5f\n", time_taken_output);

    return 0;
}
