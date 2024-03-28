#ifndef VERTEX_H
#define VERTEX_H

typedef struct vertex Vertex;

Vertex *vertex_init(char *id, double *position);

char *vertex_get_id(Vertex *v);

double *vertex_get_position(Vertex *v);

double vertex_distance_between(Vertex *v1, Vertex *v2, int dimension);

void vertex_destroy(void *v);

void vertex_print(Vertex *v, int d);

#endif