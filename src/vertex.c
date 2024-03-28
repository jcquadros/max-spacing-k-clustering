#include "vertex.h"
#include "math.h"
#include <stdlib.h>

struct vertex {
    char *id;
    double *position;
};

Vertex *vertex_init(char *id, double *position){
    Vertex *v = (Vertex *)calloc(1, sizeof(Vertex));
    v->id = id;
    v->position = position;
    return v;
}

char *vertex_get_id(Vertex *v){
    return v->id;
}

double *vertex_get_position(Vertex *v){
    return v->position;
}

double vertex_distance_between(Vertex *v1, Vertex *v2, int dimension){
    
    return 0.0;
}

void vertex_destroy(void *v){
    Vertex *s = (Vertex *)v;
    free(s->id);
    free(s->position);
    free(s);
}