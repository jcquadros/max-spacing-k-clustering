#ifndef EDGE_VECTOR_H
#define EDGE_VECTOR_H

#include "edge.h"

/*
 * EdgeVector
 * ----------
 * Estrutura de dados para armazenar um vetor dinâmico de arestas.
 */

typedef struct edge_vector EdgeVector;  // Tipo opaco para representar um vetor de arestas.

/*
 * edge_vector_init
 * ----------------
 * Inicializa um vetor dinâmico de arestas com o tamanho especificado.
 *
 * Parâmetros:
 *   - size: o tamanho inicial do vetor.
 *
 * Retorno:
 *   - Um ponteiro para a estrutura EdgeVector inicializada.
 */
EdgeVector *edge_vector_init(int size);

/*
 * edge_vector_push_back
 * ----------------------
 * Adiciona uma nova aresta ao final do vetor.
 *
 * Parâmetros:
 *   - ev: o vetor de arestas.
 *   - vertex1: índice do primeiro vértice da aresta.
 *   - vertex2: índice do segundo vértice da aresta.
 *   - weight: peso da aresta.
 */
void edge_vector_push_back(EdgeVector *ev, int vertex1, int vertex2, double weight);

/*
 * edge_vector_get
 * ---------------
 * Retorna a aresta no índice especificado.
 *
 * Parâmetros:
 *   - ev: o vetor de arestas.
 *   - idx: o índice da aresta desejada.
 *
 * Retorno:
 *   - Um ponteiro para a aresta no índice especificado.
 */
Edge *edge_vector_get(EdgeVector *ev, int idx);

/*
 * edge_vector_size
 * ----------------
 * Retorna o tamanho atual do vetor de arestas.
 *
 * Parâmetros:
 *   - ev: o vetor de arestas.
 *
 * Retorno:
 *   - O tamanho atual do vetor de arestas.
 */
int edge_vector_size(EdgeVector *ev);

/*
 * edge_vector_sort
 * ----------------
 * Ordena o vetor de arestas com base em seus pesos.
 *
 * Parâmetros:
 *   - ev: o vetor de arestas a ser ordenado.
 */
void edge_vector_sort(EdgeVector *ev);


/*
 * edge_vector_destroy
 * -------------------
 * Libera a memória alocada para o vetor de arestas.
 *
 * Parâmetros:
 *   - ev: o vetor de arestas a ser destruído.
 */
void edge_vector_destroy(EdgeVector *ev);

#endif
