#ifndef IO_H
#define IO_H

#include "vertex_vector.h"
#include "union_find.h"

/*
 * read_input
 * ----------
 * Lê o arquivo de entrada contendo informações sobre os vértices e suas posições,
 * e inicializa um vetor de vértices a partir dessas informações.
 *
 * Parâmetros:
 *   - input_file: o nome do arquivo de entrada.
 *   - dimension: ponteiro para armazenar a dimensão do espaço (R^n).
 *
 * Retorno:
 *   - Um ponteiro para o vetor de vértices lido do arquivo de entrada.
 */
VertexVector *read_input(char *input_file, int *dimension);

/*
 * write_output
 * ------------
 * Escreve o resultado da construção da "quase" Árvore Geradora Mínima (quase-MST)
 * e os vértices correspondentes a cada grupo em um arquivo de saída.
 *
 * Parâmetros:
 *   - vertex_vector: o vetor de vértices.
 *   - mst: a estrutura Union-Find representando a quase-MST.
 *   - output_file: o nome do arquivo de saída.
 */
void write_output(VertexVector *vertex_vector, UF *mst, char *output_file);

#endif // IO_H
