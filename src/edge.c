#include "edge.h"
#include <stdlib.h>
#include <stdio.h>



void edge_set(Edge *ed, int vertex1, int vertex2, double weight)
{
    ed->vertex1 = vertex1;
    ed->vertex2 = vertex2;
    ed->weight = weight;
}

int edge_get_vertex1(Edge *ed)
{
    return ed->vertex1;
}

int edge_get_vertex2(Edge *ed)
{
    return ed->vertex2;
}

double edge_get_weight(Edge *ed)
{
    return ed->weight;
}

void edge_destroy(Edge *ed)
{
    // nada
}