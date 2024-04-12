#ifndef UNION_FIND_H
#define UNION_FIND_H

/*
 * Union-Find Data Structure
 * ------------------------------------------
 * Implementação de uma estrutura de dados Union-Find para representar conexões entre elementos.
 */

typedef struct uf UF;  // Tipo opaco para representar uma estrutura Union-Find.

/*
 * uf_init
 * -------
 * Inicializa uma estrutura Union-Find com o tamanho especificado.
 *
 * Parâmetros:
 *   - size: o tamanho da estrutura Union-Find.
 *
 * Retorno:
 *   - Um ponteiro para a estrutura Union-Find.
 */
UF *uf_init(int size);

/*
 * uf_find
 * -------
 * Retorna a raiz do componente ao qual o elemento 'i' pertence.
 *
 * Parâmetros:
 *   - uf: a estrutura Union-Find.
 *   - i: o índice do elemento cuja raiz deve ser encontrado.
 *
 * Retorno:
 *   - Raiz do componente ao qual o elemento 'i' pertence.
 */
int uf_find(UF *uf, int i);

/*
 * uf_union
 * --------
 * Une os elementos 'p' e 'q'.
 *
 * Parâmetros:
 *   - uf: a estrutura Union-Find.
 *   - p: o índice do primeiro elemento.
 *   - q: o índice do segundo elemento.
 */
void uf_union(UF *uf, int p, int q);

/*
 * uf_destroy
 * ----------
 * Libera a memória alocada para a estrutura Union-Find.
 *
 * Parâmetros:
 *   - uf: a estrutura Union-Find a ser destruída.
 */
void uf_destroy(UF *uf);

#endif
