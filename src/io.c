#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Custo Numero de tokens da linha 1 do nome e N dimensoes + custo de adicionar no vetor que é constante
// estou analizando aquantidade de strtok
int process_line(char *line, VertexVector *vertex_vector, int aloc)
{
    int n = 0;
    char *name = strtok(line, ",");
    char *token = strtok(NULL, ",");

    if (token == NULL)
    {
        exit(1);
    }

    double *coord = (double *)malloc((aloc + 1) * sizeof(double));

    while (token)
    {
        coord[n] = atof(token);

        if (n == aloc)
        {
            aloc++;
            coord = (double *)realloc(coord, (aloc + 1) * sizeof(double));
        }

        n++;
        token = strtok(NULL, ",");
    }

    vertex_vector_push_back(vertex_vector, name, coord);

    return aloc;
}
// Ordem N*process_line (N quantidade de linhas do arquivo / vertices)
VertexVector *read_input(char *input_file, int *dimension)
{
    FILE *file = fopen(input_file, "r");
    if (file == NULL){
        exit(1);
    }

    VertexVector *vertex_vector = vertex_vector_init(10);
    char *line = NULL;
    size_t size = 0;
    int len;
    int aloc = 1;

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        aloc = process_line(line, vertex_vector, aloc);
    }

    *dimension = aloc;

    free(line);
    fclose(file);
    return vertex_vector;
}

// Ordem N^2/2
void write_output(VertexVector *vertex_vector, UF *mst, char *output_file)
{
    FILE *file = fopen(output_file, "w");
    if (file == NULL)
    {
        exit(1);
    }
    char *marked = (char *)calloc(vertex_vector_size(vertex_vector), sizeof(char));
    int curr_group = -1;
    int size = vertex_vector_size(vertex_vector);

    for (int i = 0; i < size; i++)
    {
        int next_group = uf_find(mst, i);
        if (!marked[next_group])
        {
            curr_group = next_group;
            for (int j = i; j < size; j++)
            {
                if (uf_find(mst, j) == curr_group)
                    fprintf(file, "%s,", vertex_get_id(vertex_vector_get(vertex_vector, j)));
            }
            fseek(file, -1, SEEK_CUR); // Move o cursor uma posição antes pra remover a virgula
            fprintf(file, "\n");
            
        }
        marked[curr_group] = 1;
    }
    free(marked);
    fclose(file);
}