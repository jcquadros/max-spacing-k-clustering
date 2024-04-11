#ifndef VERTEX_VECTOR_H
#define VERTEX_VECTOR_H

#include "vertex.h"

typedef struct vertex_vector VertexVector;

VertexVector *vertex_vector_init(int size);

void vertex_vector_push_back(VertexVector *vv, char *id, double *position);

Vertex *vertex_vector_get(VertexVector *vv, int idx);

int vertex_vector_size(VertexVector *vv);

void vertex_vector_sort(VertexVector *vv);

int vertex_vector_compare(const void *a, const void *b);

void vertex_vector_destroy(VertexVector *vv);

#endif
