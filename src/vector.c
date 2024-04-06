#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

struct vector
{
    data_vector *data;
    destroy_vector destroy_fn;
    compare_vector compare_fn;
    int size;
    int capacity;
};

Vector *vector_init(int size, destroy_vector destroy_fn, compare_vector compare_fn)
{
    if (size <= 0)
    {
        printf("Size must be greater than 0\n");
        exit(1);
    }

    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    v->destroy_fn = destroy_fn;
    v->compare_fn = compare_fn;
    v->size = 0;
    v->capacity = size;
    v->data = (data_vector *)calloc(v->capacity, sizeof(data_vector));
    return v;
}

void vector_push_back(Vector *v, data_vector data)
{
    if (v->size >= v->capacity)
    {
        v->capacity *= 2;
        v->data = (data_vector *)realloc(v->data, v->capacity * sizeof(data_vector));
    }
    v->data[v->size] = data;
    v->size++;
}

data_vector vector_pop_back(Vector *v)
{
    if (v->size <= 0)
    {
        printf("Empty Vector\n");
        exit(1);
    }

    v->size--;
    data_vector data = v->data[v->size];
    v->data[v->size] = NULL;
    return data;
}

int vector_size(Vector *v)
{
    return v->size;
}

data_vector vector_get(Vector *v, int idx)
{
    if (idx < 0 || idx >= v->size)
    {
        printf("Invalid idx '%d' for Vector with size '%d'.\n", idx, v->size);
        exit(1);
    }
    return v->data[idx];
}

void vector_destroy(Vector *v)
{
    if (v->destroy_fn)
    {
        for (int i = 0; i < v->size; i++)
        {
            v->destroy_fn(v->data[i]);
        }
    }
    free(v->data);
    free(v);
}

void vector_sort(Vector *v)
{
    qsort(v->data, v->size, sizeof(data_vector), v->compare_fn);
}
