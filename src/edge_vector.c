#include "edge_vector.h"
#include <stdlib.h>
#include <stdio.h>

struct edge_vector
{
    Edge *data;
    int size;
    int capacity;
};

EdgeVector *edge_vector_init(int size)
{
    if (size <= 0)
    {
        printf("Size must be greater than 0\n");
        exit(1);
    }

    EdgeVector *ev = (EdgeVector *)calloc(1, sizeof(EdgeVector));
    ev->size = 0;
    ev->capacity = size;
    ev->data = (Edge *)calloc(ev->capacity, sizeof(Edge));
    return ev;
}

void edge_vector_push_back(EdgeVector *ev, int vertex1, int vertex2, double weight)
{
    if (ev->size >= ev->capacity)
    {
        ev->capacity *= 2;
        ev->data = (Edge *)realloc(ev->data, ev->capacity * sizeof(Edge));
    }
    Edge *edge = &(ev->data[ev->size]);
    ev->size++;
    edge_set(edge, vertex1, vertex2, weight);
}

Edge *edge_vector_get(EdgeVector *ev, int idx)
{
    if (idx < 0 || idx >= ev->size)
    {
        printf("Invalid idx '%d' for EdgeVector with size '%d'.\n", idx, ev->size);
        exit(1);
    }
    return &(ev->data[idx]);
}

int edge_vector_size(EdgeVector *ev)
{
    return ev->size;
}

void edge_vector_sort(EdgeVector *ev)
{
    qsort(ev->data, ev->size, sizeof(Edge), edge_vector_compare);
}

int edge_vector_compare(const void *a, const void *b)
{
    Edge *edge1 = (Edge *)a;
    Edge *edge2 = (Edge *)b;

    if (edge_get_weight(edge1) < edge_get_weight(edge2))
    {
        return -1;
    }
    else if (edge_get_weight(edge1) > edge_get_weight(edge2))
    {
        return 1;
    }
    return 0;
}

void edge_vector_destroy(EdgeVector *ev)
{
    free(ev->data);
    free(ev);
}
