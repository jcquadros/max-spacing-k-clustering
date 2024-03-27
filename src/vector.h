#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector Vector;
typedef void* data_vector;
typedef void (*destroy_vector)(data_vector);

/*Cria vetor de tamanho 'size' */
Vector *vector_init(int size, destroy_vector destroy_fn);

int vector_size(Vector *v);

/*Insere na ultima posição do vetor. Se necessário, realoca mais memória*/
void vector_push_back(data_vector data);

/*Remove da ultima posição do vetor e retorna o item removido*/
data_vector vector_pop_back();

/*Recupera um item de uma dada posição*/
void vector_get(int idx);

/*Desaloca o vetor inclusive todos os itens*/
void vector_destroy();

#endif 