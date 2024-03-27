#include "vector.h"
#include <stdlib.h>

struct vector{
    data_vector *data;
    destroy_vector destroy_fn;
    int size;
    int capacity;
};


Vector *vector_init(int size, destroy_vector destroy_fn){
    // TODO
    return NULL;
}


void vector_push_back(data_vector data){
    //TODO
}

data_vector vector_pop_back(){
    //TODO
    return NULL;
}

int vector_size(Vector *v){
    // TODO
    return 0;
}

void vector_get(int idx){
    //TODO
}

void vector_destroy(){
    //TODO
}