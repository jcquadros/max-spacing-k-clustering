#include "edge.h"
#include <stdlib.h>

struct edge{
    int vertex1;
    int vertex2;
    double weight;
}; 

Edge *edge_init(int vertex1, int vertex2, double weight){
    Edge * ed = (Edge*) malloc(sizeof(Edge));
    ed->vertex1 = vertex1;
    ed->vertex2 = vertex2;
    ed->weight = weight;

    return ed;
}

int edge_get_vertex1(Edge *ed){
    return ed->vertex1;
}

int edge_get_vertex2(Edge *ed){
    return ed->vertex2;
}

double edge_get_weight(Edge *ed){
    return ed->weight;
}

void edge_destroy(void *ed){
    free((Edge*)ed);
}

int edge_compare(Edge *ed1, Edge *ed2){
    if(ed1->weight > ed2->weight){
        return 1;
    }else if(ed1->weight < ed2->weight){
        return -1;
    }
    return 0;
}