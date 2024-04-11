#ifndef EDGE_VECTOR_H
#define EDGE_VECTOR_H

#include "edge.h"

typedef struct edge_vector EdgeVector;

EdgeVector *edge_vector_init(int size);

void edge_vector_push_back(EdgeVector *ev, int vertex1, int vertex2, double weight);

Edge *edge_vector_get(EdgeVector *ev, int idx);

int edge_vector_size(EdgeVector *ev);

void edge_vector_sort(EdgeVector *ev);

int edge_vector_compare(const void *a, const void *b);

void edge_vector_destroy(EdgeVector *ev);

#endif
