#include "vector.h"
#include "edge.h"
#include "vertex.h"
#include "union_find.h"
#include <stdio.h>
#include <stdlib.h>

void setup(char *directory, Vector *vertex_vector){
    // verificar se o arquivo de entrada existe, caso contrario encerrar programa 
    // ler entrada e salvar dados no vetor de vertices
      
}

void calculate_distance(Vector *edge_vector, Vector *vertex_vector){
    int size_vv = vector_size(vertex_vector);
    for(int i = 0; i < size_vv - 1; i++){
        for(int j = i+1; j < size_vv; j++){
            // para cada posição do vetor de vértices, calcular a distancia com os demais
            // criar aresta (i, j e distancia) e inserir no vetor de arestas
        }
    }
}

int main(int argc, char *argv){
    printf("%d\n", argc);
    if(argc < 3){
        // formato de entrada: ./trab1 entrada saida
        return 1;
    }
    Vector *vertex_vector = vector_init(0, vertex_destroy);
    setup(argv[1], vertex_vector);

    int n_edges = vector_size(vertex_vector)-1;
    Vector *edge_vector = vector_init(n_edges, edge_destroy);
    calculate_distance(edge_vector, vertex_vector);

    // ordenar
    // calcular a arvore minima
    // remover k ultimos
    // salvar resultado
    return 0;
}