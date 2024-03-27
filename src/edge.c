#include "edge.h"
#include <stdlib.h>

struct edge{
    int vertex1;
    int vertex2;
    double weight;
}; 

Edge *edge_init(int vertex1, int vertex2, double weight){
    // TODO
    return NULL;
}

int edge_get_vertex1(Edge *ed){
    // TODO
    return 0;
}

int edge_get_vertex2(Edge *ed){
    // TODO
    return 0;
}

double edge_get_weight(Edge *ed){
    // TODO
    return 0.0;
}


void edge_destroy(void *ed){
    // TODO
}

int edge_compare(Edge *ed1, Edge *ed2){
    // TODO
    return 0;
}