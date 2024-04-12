#ifndef VERTEX_VECTOR_H
#define VERTEX_VECTOR_H

#include "vertex.h"

/*
 * VertexVector
 * ------------
 * Estrutura de dados para armazenar um vetor dinâmico de vértices.
 */

typedef struct vertex_vector VertexVector;  // Tipo opaco para representar um vetor de vértices.

/*
 * vertex_vector_init
 * ------------------
 * Inicializa um vetor dinâmico de vértices com o tamanho especificado.
 *
 * Parâmetros:
 *   - size: o tamanho inicial do vetor.
 *
 * Retorno:
 *   - Um ponteiro para a estrutura VertexVector inicializada.
 */
VertexVector *vertex_vector_init(int size);

/*
 * vertex_vector_push_back
 * ------------------------
 * Adiciona um novo vértice ao final do vetor.
 *
 * Parâmetros:
 *   - vv: o vetor de vértices.
 *   - id: identificador do vértice.
 *   - position: conjunto de coordenadas em R^N representando a posição do vértice.
 */
void vertex_vector_push_back(VertexVector *vv, char *id, double *position);

/*
 * vertex_vector_get
 * -----------------
 * Retorna o vértice no índice especificado.
 *
 * Parâmetros:
 *   - vv: o vetor de vértices.
 *   - idx: o índice do vértice desejado.
 *
 * Retorno:
 *   - Um ponteiro para o vértice no índice especificado.
 */
Vertex *vertex_vector_get(VertexVector *vv, int idx);

/*
 * vertex_vector_size
 * ------------------
 * Retorna o tamanho atual do vetor de vértices.
 *
 * Parâmetros:
 *   - vv: o vetor de vértices.
 *
 * Retorno:
 *   - O tamanho atual do vetor de vértices.
 */
int vertex_vector_size(VertexVector *vv);

/*
 * vertex_vector_sort
 * ------------------
 * Ordena o vetor de vértices com base em seus identificadores.
 *
 * Parâmetros:
 *   - vv: o vetor de vértices a ser ordenado.
 */
void vertex_vector_sort(VertexVector *vv);

/*
 * vertex_vector_compare
 * ---------------------
 * Função de comparação a ser usada pelo algoritmo de ordenação para comparar
 * os identificadores de dois vértices.
 *
 * Parâmetros:
 *   - a: ponteiro para o primeiro vértice.
 *   - b: ponteiro para o segundo vértice.
 *
 * Retorno:
 *   - Um valor negativo se o identificador de 'a' for menor que o de 'b',
 *     zero se forem iguais, ou um valor positivo se o identificador de 'a'
 *     for maior que o de 'b'.
 */
int vertex_vector_compare(const void *a, const void *b);

/*
 * vertex_vector_destroy
 * ---------------------
 * Libera a memória alocada para o vetor de vértices.
 *
 * Parâmetros:
 *   - vv: o vetor de vértices a ser destruído.
 */
void vertex_vector_destroy(VertexVector *vv);

#endif
