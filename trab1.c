#include "vector.h"
#include "edge.h"
#include "vertex.h"
#include "union_find.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void setup(char *directory, Vector *vertex_vector){

    // verificar se o arquivo de entrada existe, caso contrario encerrar programa 
    // ler entrada e salvar dados no vetor de vertices
    
    FILE * file;
    file = fopen(directory, "r"); 
    
    if(file == NULL)
        exit(printf("Arquivo de entradas não encontrado!\nNome: %s\n", directory));
    
    char line[100];
    
    while (fgets(line, sizeof(line), file) != NULL) {

        char *name = strtok(line, ",");
        char *aux = strtok(NULL, ",");
        
        int n = 0;
        double * coord = (double*)malloc(10*sizeof(double));
        
        while(1){
            coord[n] = atof(aux);
            //printf("%f ", coord[n]);
            n++;
            aux = strtok(NULL, ",");
            if(aux == NULL)break;
        }
        Vertex * v = vertex_init(name, coord);
    }
    
    fclose(file);
}

void calculate_distance(Vector *edge_vector, Vector *vertex_vector, int dimension){
    int size_vv = vector_size(vertex_vector);
    for(int i = 0; i < size_vv - 1; i++){
        for(int j = i+1; j < size_vv; j++){
            Vertex *vertex1 = vector_get(vertex_vector, i);
            Vertex *vertex2 = vector_get(vertex_vector, j);
            double weight = vertex_distance_between(vertex1, vertex2, dimension);
            
            Edge *edge = edge_init(i, j, weight);
            vector_push_back(edge, edge_vector);
        }
    }
}

int main(int argc, char **argv){
    
    if(argc < 3){
        // formato de entrada: ./trab1 entrada saida
        return 1;
    }
    int dimension =0;
    Vector *vertex_vector = vector_init(0, vertex_destroy);
    setup(argv[1], vertex_vector);

    int n_edges = vector_size(vertex_vector)-1;
    Vector *edge_vector = vector_init(n_edges, edge_destroy);
    calculate_distance(edge_vector, vertex_vector, dimension);

    // ordenar
    // calcular a arvore minima
    // remover k ultimos
    // salvar resultado
    return 0;
}