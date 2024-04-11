#include "vertex.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void vertex_set(Vertex *v, char *id, double *position)
{
    v->id = strdup(id);
    v->position = position;
}

char *vertex_get_id(Vertex *v)
{
    return v->id;
}

double *vertex_get_position(Vertex *v)
{
    return v->position;
}

double vertex_distance_between(Vertex *v1, Vertex *v2, int dimension)
{
    double sum = 0;
    double dif = 0;
    for (int i = 0; i < dimension; i++)
    {
        dif = v1->position[i] - v2->position[i];
        sum += pow(dif, 2);
    }
    return sqrt(sum);
}

void vertex_destroy(Vertex *v)
{
    free(v->id);
    free(v->position);
}
