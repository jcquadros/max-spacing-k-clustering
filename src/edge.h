#ifndef EDGE_H
#define EDGE_H

typedef struct edge
{
    int vertex1;
    int vertex2;
    double weight;
}Edge;

void edge_set(Edge* ed, int vertex1, int vertex2, double weight);

int edge_get_vertex1(Edge *ed);

int edge_get_vertex2(Edge *ed);

double edge_get_weight(Edge *ed);

void edge_destroy(Edge *ed);

#endif