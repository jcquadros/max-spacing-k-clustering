#include "vertex.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct vertex
{
    char *id;
    double *position;
};

Vertex *vertex_init(char *id, double *position)
{
    Vertex *v = (Vertex *)calloc(1, sizeof(Vertex));
    v->id = strdup(id);
    v->position = position;
    return v;
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

void vertex_destroy(void *v)
{
    Vertex *s = (Vertex *)v;
    free(s->id);
    free(s->position);
    free(s);
}

void vertex_print(Vertex *v, int d)
{
    printf("%s,", v->id);
    int n = 0;

    while (n < d)
    {
        double p = v->position[n];
        
        if(n+1 == d)
            printf("%.15f\n", p);
        else
            printf("%.15f,", p);
        
        n++;
    }
}
