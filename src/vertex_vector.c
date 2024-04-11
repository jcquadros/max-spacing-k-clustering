#include "vertex_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct vertex_vector
{
    Vertex *data;
    int size;
    int capacity;
};

VertexVector *vertex_vector_init(int size)
{
    if (size <= 0)
    {
        printf("Size must be greater than 0\n");
        exit(1);
    }

    VertexVector *vv = (VertexVector *)calloc(1, sizeof(VertexVector));
    vv->size = 0;
    vv->capacity = size;
    vv->data = (Vertex *)calloc(vv->capacity, sizeof(Vertex));
    return vv;
}

void vertex_vector_push_back(VertexVector *vv, char *id, double *position)
{
    if (vv->size >= vv->capacity)
    {
        vv->capacity *= 2;
        vv->data = (Vertex *)realloc(vv->data, vv->capacity * sizeof(Vertex));
    }
    Vertex *vertex = &(vv->data[vv->size]);
    vv->size++;
    vertex_set(vertex, id, position);
}

Vertex *vertex_vector_get(VertexVector *vv, int idx)
{
    if (idx < 0 || idx >= vv->size)
    {
        printf("Invalid idx '%d' for VertexVector with size '%d'.\n", idx, vv->size);
        exit(1);
    }
    return &(vv->data[idx]);
}

int vertex_vector_size(VertexVector *vv)
{
    return vv->size;
}

void vertex_vector_sort(VertexVector *vv)
{
    qsort(vv->data, vv->size, sizeof(Vertex), vertex_vector_compare);
}

int vertex_vector_compare(const void *a, const void *b)
{
    Vertex vertex1 = *(Vertex *)a;
    Vertex vertex2 = *(Vertex *)b;

    // Comparação baseada nos IDs dos vértices
    return strcmp(vertex_get_id(&vertex1), vertex_get_id(&vertex2));
}

void vertex_vector_destroy(VertexVector *vv)
{
    for (int i = 0; i < vv->size; i++)
    {
        vertex_destroy(&(vv->data[i]));
    }
    free(vv->data);
    free(vv);
}
