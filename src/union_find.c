#include "union_find.h"
#include <stdlib.h>
#include <stdio.h>

struct uf
{
    int *id;
    int *sz;
    int size;
};

UF *uf_init(int size)
{
    UF *uf = (UF *)malloc(sizeof(UF));
    uf->id = (int *)malloc(size * sizeof(int));
    uf->sz = (int *)malloc(size * sizeof(int));
    uf->size = size;

    for (int i = 0; i < size; i++)
    {
        uf->id[i] = i;
        uf->sz[i] = 1;
    }
    return uf;
}

int uf_find(UF *uf, int i)
{
    while (i != uf->id[i])
    {
        uf->id[i] = uf->id[uf->id[i]];
        i = uf->id[i];
    }
    return i;
}

void uf_union(UF *uf, int p, int q)
{
    int i = uf_find(uf, p);
    int j = uf_find(uf, q);

    if (i == j)
        return;
    if (uf->sz[i] < uf->sz[j])
    {
        uf->id[i] = j;
        uf->sz[j] += uf->sz[i];
    }
    else
    {
        uf->id[j] = i;
        uf->sz[i] += uf->sz[j];
    }
}

void uf_destroy(UF *uf)
{
    free(uf->id);
    free(uf->sz);
    free(uf);
}

