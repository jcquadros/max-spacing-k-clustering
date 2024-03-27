#ifndef VERTEX_H
#define VERTEX_H

typedef struct vertex Vertex;

Vertex *vertex_init(char *id, int *position);

char *vertex_get_id(Vertex *v);

int *vertex_get_position(Vertex *v);

double vertex_distance_between(Vertex *v1, Vertex *v2);

void vertex_destroy(void *v);

#endif