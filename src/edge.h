#ifndef EDGE_H
#define EDGE_H

/*
 * Edge
 * ----
 * Estrutura de dados para representar uma aresta entre dois vértices em um grafo ponderado.
 */

typedef struct edge
{
    int vertex1;
    int vertex2;
    double weight;
}Edge; // Tipo não opaco para representar uma aresta.


/*
 * edge_set
 * --------
 * Define as propriedades de uma aresta com os vértices e o peso especificados.
 *
 * Parâmetros:
 *   - ed: a aresta a ser configurada.
 *   - vertex1: índice do primeiro vértice da aresta.
 *   - vertex2: índice do segundo vértice da aresta.
 *   - weight: peso da aresta.
 */
void edge_set(Edge *ed, int vertex1, int vertex2, double weight);

/*
 * edge_get_vertex1
 * ----------------
 * Retorna o índice do primeiro vértice da aresta.
 *
 * Parâmetros:
 *   - ed: a aresta.
 *
 * Retorno:
 *   - O índice do primeiro vértice da aresta.
 */
int edge_get_vertex1(Edge *ed);

/*
 * edge_get_vertex2
 * ----------------
 * Retorna o índice do segundo vértice da aresta.
 *
 * Parâmetros:
 *   - ed: a aresta.
 *
 * Retorno:
 *   - O índice do segundo vértice da aresta.
 */
int edge_get_vertex2(Edge *ed);

/*
 * edge_get_weight
 * ---------------
 * Retorna o peso da aresta.
 *
 * Parâmetros:
 *   - ed: a aresta.
 *
 * Retorno:
 *   - O peso da aresta.
 */
double edge_get_weight(Edge *ed);

/*
 * edge_destroy
 * ------------
 * Libera a memória alocada para a aresta.
 *
 * Parâmetros:
 *   - ed: a aresta a ser destruída.
 */
void edge_destroy(Edge *ed);

/*
 * edge_compare
 * -------------------
 * Função de comparação a ser usada pelo algoritmo de ordenação para comparar
 * os pesos de duas arestas.
 *
 * Parâmetros:
 *   - a: ponteiro para a primeira aresta.
 *   - b: ponteiro para a segunda aresta.
 *
 * Retorno:
 *   - Um valor negativo se o peso da aresta 'a' for menor que o da aresta 'b',
 *     zero se forem iguais, ou um valor positivo se o peso da aresta 'a'
 *     for maior que o da aresta 'b'.
 */
int edge_compare(const void *a, const void *b);

#endif
