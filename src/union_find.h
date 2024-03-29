#ifndef UNION_FIND_H
#define UNION_FIND_H

typedef struct uf UF;

UF *uf_init(int size);

int uf_find(UF *uf, int i);

void uf_union(UF *uf, int p, int q);

void uf_destroy(UF *uf);

void print_uf(UF *uf);

#endif