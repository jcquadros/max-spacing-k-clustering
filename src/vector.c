#include "vector.h"
#include <stdlib.h>

struct vector{
    data_vector *data;
    destroy_vector destroy_fn;
    int size;
    int capacity;
};


Vector *vector_init(int size, destroy_vector destroy_fn){
    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    v->destroy_fn = destroy_fn;
    v->size = 0;
    v->capacity = size;
    v->data = (data_vector *)calloc(v->capacity, sizeof(data_vector));
    return v;
}


void vector_push_back(data_vector data, Vector *v){
    if(v->size >= v->capacity){
        v->capacity *= 2;
        v->data = (data_vector *)realloc(v->data, v->capacity * sizeof(data_vector));
    }
    v->data[v->size] = data;
    v->size++;
}

data_vector vector_pop_back(Vector *v){
    if (v->size <= 0)
    {
        printf("Empty Vector");
        exit(1);
    }

    v->size--;
    data_vector data = v->data[v->size];
    v->data[v->size] = NULL;
    return data;
}

int vector_size(Vector *v){
    return v->size;
}

data_vector vector_get(int idx, Vector *v){
    if (idx < 0 || idx >= v->size)
    {
        printf("Invalid idx '%d' for Vector with size '%d'.\n", idx, v->size);
        exit(1);
    }
    return v->data[idx];
}

void vector_destroy(Vector *v){
    for(int i = 0; i < v->size; i++){
        v->destroy_fn(v->data[i]);
    }
    free(v);
}