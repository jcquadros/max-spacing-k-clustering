#ifndef VERTEX_H
#define VERTEX_H

/*
 * Vertex
 * ------
 * Estrutura de dados para representar um vértice em R^n.
 */

typedef struct vertex
{
    char *id;
    double *position;
}Vertex; // Tipo nao opaco para representar um vertice.

/*
 * vertex_set
 * ----------
 * Define as propriedades de um vértice com o identificador e a posição especificados.
 *
 * Parâmetros:
 *   - v: o vértice a ser configurado.
 *   - id: identificador do vértice.
 *   - position: posição do vértice em R^n.
 */
void vertex_set(Vertex *v, char *id, double *position);

/*
 * vertex_get_id
 * -------------
 * Retorna o identificador do vértice.
 *
 * Parâmetros:
 *   - v: o vértice.
 *
 * Retorno:
 *   - O identificador do vértice.
 */
char *vertex_get_id(Vertex *v);

/*
 * vertex_get_position
 * -------------------
 * Retorna a posição do vértice.
 *
 * Parâmetros:
 *   - v: o vértice.
 *
 * Retorno:
 *   - Um ponteiro para a posição do vértice.
 */
double *vertex_get_position(Vertex *v);

/*
 * vertex_distance_between
 * ------------------------
 * Calcula a distância Euclidiana entre dois vértices.
 *
 * Parâmetros:
 *   - v1: o primeiro vértice.
 *   - v2: o segundo vértice.
 *   - dimension: a dimensão do espaço.
 *
 * Retorno:
 *   - A distância Euclidiana entre os dois vértices.
 */
double vertex_distance_between(Vertex *v1, Vertex *v2, int dimension);

/*
 * vertex_destroy
 * --------------
 * Libera a memória alocada para o vértice.
 *
 * Parâmetros:
 *   - v: o vértice a ser destruído.
 */
void vertex_destroy(Vertex *v);

#endif
