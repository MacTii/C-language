#include <stdio.h>
#include <stdlib.h>
#include "matrix_utils.h"

#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8
#define FILE_FAIL 2
#define FILE_CORRUPTED 3
#define SUCCESS 0

int matrix_create(struct matrix_t *m, int width, int height)
{
    if (m == NULL || width <= 0 || height <= 0)
        return 1;
    m->ptr = (int **)malloc(sizeof(int *) * height);
    if (m->ptr == NULL)
        return 2;
    int i;
    for (i = 0; i < height; i++)
    {
        *(m->ptr + i) = (int *)malloc(sizeof(int) * width);
        if (*(m->ptr + i) == NULL)
        {
            int j;
            for (j = 0; j < i; j++)
                free(*(m->ptr + j));
            free(m->ptr);
            return 2;
        }
    }
    m->height = height;
    m->width = width;
    return 0;
}

int matrix_read(struct matrix_t *m)
{
    if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0)
        return 1;
    int i, j;
    for (i = 0; i < m->height; i++)
    {
        for (j = 0; j < m->width; j++)
        {
            int x = scanf("%d", (*(m->ptr + i) + j));
            if (x != 1)
                return 2;
        }
    }
    return 0;
}

void matrix_display(const struct matrix_t *m)
{
    if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0)
        return;
    int i, j;
    for (i = 0; i < m->height; i++)
    {
        for (j = 0; j < m->width; j++)
            printf("%d ", *(*(m->ptr + i) + j));
        printf("\n");
    }
}

void matrix_destroy(struct matrix_t *m)
{
    if (m == NULL || m->ptr == NULL || m->height <= 0 || m->width <= 0)
        return;
    int i;
    for (i = 0; i < m->height; i++)
        free(*(m->ptr + i));
    free(m->ptr);
}

struct matrix_t *matrix_create_struct(int width, int height)
{
    if (width < 1 || height < 1)
        return NULL;

    struct matrix_t *m = (struct matrix_t *)calloc(1, sizeof(struct matrix_t));
    if (m == NULL)
        return NULL;

    m->height = height;
    m->width = width;

    m->ptr = (int **)calloc(m->height, sizeof(int *));
    if (m->ptr == NULL)
        return free(m), NULL;

    for (int i = 0; i < height; i++)
    {
        *(m->ptr + i) = (int *)calloc(m->width, sizeof(int));
        if (*(m->ptr + i) == NULL)
        {
            for (int j = 0; j < i; j++)
                free(*(m->ptr + j));
            return free(m), free(m->ptr), NULL;
        }
    }
    return m;
}

void matrix_destroy_struct(struct matrix_t **m)
{
    if (m == NULL)
        return;

    for (int i = 0; i < (*m)->height; i++)
        free(*((*m)->ptr + i));
    free((*m)->ptr);
    free(*m);
    *m = NULL;
}

struct matrix_t *matrix_transpose(const struct matrix_t *m)
{
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1)
        return NULL;

    struct matrix_t *temp = (struct matrix_t *)calloc(1, sizeof(struct matrix_t));
    if (temp == NULL)
        return NULL;

    temp->width = m->height;
    temp->height = m->width;

    temp->ptr = (int **)calloc(temp->height, sizeof(int *));
    if (temp->ptr == NULL)
        return free(temp), NULL;

    for (int i = 0; i < temp->height; i++)
    {
        *(temp->ptr + i) = (int *)calloc(temp->width, sizeof(int));
        if (*(temp->ptr + i) == NULL)
        {
            for (int j = 0; j < i; j++)
                free(*(temp->ptr + j));
            return free(temp->ptr), free(temp), NULL;
        }
    }

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
            *(*(temp->ptr + j) + i) = *(*(m->ptr + i) + j);
    }

    return temp;
}

int matrix_save_b(const struct matrix_t *m, const char *filename)
{
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1 || filename == NULL)
        return INCORRECT_INPUT;

    FILE *f;
    f = fopen(filename, "wb");
    if (f == NULL)
        return FILE_FAIL;

    fwrite(&m->width, 1, sizeof(int), f);
    fwrite(&m->height, 1, sizeof(int), f);

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
            fwrite(*(m->ptr + i) + j, 1, sizeof(int), f);
    }

    fclose(f);
    return SUCCESS;
}

int matrix_save_t(const struct matrix_t *m, const char *filename)
{
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1 || filename == NULL)
        return INCORRECT_INPUT;

    FILE *f;
    f = fopen(filename, "w");
    if (f == NULL)
        return FILE_FAIL;

    fprintf(f, "%d %d\n", m->width, m->height);

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
            fprintf(f, "%d ", *(*(m->ptr + i) + j));
        fprintf(f, "\n");
    }

    fclose(f);
    return SUCCESS;
}