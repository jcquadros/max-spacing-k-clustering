#include <stdio.h>
#include <stdlib.h>
#include "src/edge_vector.h"
#include "src/vertex_vector.h"

int main() {
    // Criando um VertexVector e adicionando alguns vértices
    VertexVector *vertex_vector = vertex_vector_init(5);
    double position1[2] = {1.0, 2.0};
    double position2[2] = {3.0, 4.0};
    double position3[2] = {5.0, 6.0};
    vertex_vector_push_back(vertex_vector, "A", position1);
    vertex_vector_push_back(vertex_vector, "B", position2);
    vertex_vector_push_back(vertex_vector, "C", position3);
    vertex_vector_push_back(vertex_vector, "A", position1);
    vertex_vector_push_back(vertex_vector, "B", position2);
    vertex_vector_push_back(vertex_vector, "C", position3);
    vertex_vector_push_back(vertex_vector, "A", position1);
    vertex_vector_push_back(vertex_vector, "B", position2);
    vertex_vector_push_back(vertex_vector, "C", position3);

    // Exibindo os vértices
    printf("VertexVector:\n");
    for (int i = 0; i < vertex_vector_size(vertex_vector); i++) {
        Vertex *vertex = vertex_vector_get(vertex_vector, i);
        printf("Vertex %d: ID=%s, Position=(%.2f, %.2f)\n", i+1, vertex_get_id(vertex), vertex_get_position(vertex)[0], vertex_get_position(vertex)[1]);
    }

    // Criando um EdgeVector e adicionando algumas arestas
    EdgeVector *edge_vector = edge_vector_init(5);
    edge_vector_push_back(edge_vector, 0, 1, 5.0);
    edge_vector_push_back(edge_vector, 1, 2, 7.0);
    edge_vector_push_back(edge_vector, 0, 1, 5.0);
    edge_vector_push_back(edge_vector, 1, 2, 7.0);
    edge_vector_push_back(edge_vector, 0, 1, 5.0);
    edge_vector_push_back(edge_vector, 1, 2, 7.0);
    edge_vector_push_back(edge_vector, 0, 1, 5.0);
    edge_vector_push_back(edge_vector, 1, 2, 7.0);

    // Exibindo as arestas
    printf("\nEdgeVector:\n");
    for (int i = 0; i < edge_vector_size(edge_vector); i++) {
        Edge *edge = edge_vector_get(edge_vector, i);
        printf("Edge %d: Vertex1=%d, Vertex2=%d, Weight=%.2f\n", i+1, edge_get_vertex1(edge), edge_get_vertex2(edge), edge_get_weight(edge));
    }

    // Liberando a memória alocada
    vertex_vector_destroy(vertex_vector);
    edge_vector_destroy(edge_vector);

    return 0;
}
