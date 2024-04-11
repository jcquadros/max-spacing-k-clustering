#ifndef VERTEX_H
#define VERTEX_H

typedef struct vertex
{
    char *id;
    double *position;
}Vertex;

void vertex_set(Vertex *v, char *id, double *position);

void vertex_set_id(Vertex *v, char *id);

void vertex_set_position(Vertex *v, double *position);

char *vertex_get_id(Vertex *v);

double *vertex_get_position(Vertex *v);

double vertex_distance_between(Vertex *v1, Vertex *v2, int dimension);

void vertex_destroy(Vertex *v);

#endif