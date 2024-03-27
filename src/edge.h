#ifndef EDGE_H
#define EDGE_H

typedef struct edge Edge; // aresta basicamente

Edge *edge_init(int vertex1, int vertex2, double weight);

int edge_get_vertex1(Edge *ed);

int edge_get_vertex2(Edge *ed);

double edge_get_weight(Edge *ed);

void edge_destroy(void *ed);

/*Essa função de comparação basicamente vê se o peso de uma é maior menor ou igual ao da outra.*/
int edge_compare(Edge *ed1, Edge *ed2);

#endif