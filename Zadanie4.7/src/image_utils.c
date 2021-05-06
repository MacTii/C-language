#include "image_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCORRECT_INPUT 1
#define FILE_FAIL 2
#define FILE_CORRUPTED 3
#define MEMORY_FAIL 4
#define SUCCESS 0

struct image_t *load_image_t(const char *filename, int *err_code)
{
    if (filename == NULL)
    {
        if (err_code != NULL)
            *err_code = INCORRECT_INPUT;
        return NULL;
    }

    FILE *f;
    f = fopen(filename, "r");
    if (f == NULL)
    {
        if (err_code != NULL)
            *err_code = FILE_FAIL;
        return NULL;
    }

    struct image_t *wsk = (struct image_t *)calloc(1, sizeof(struct image_t));
    if (wsk == NULL)
    {
        if (err_code != NULL)
            *err_code = MEMORY_FAIL;
        return fclose(f), NULL;
    }

    int res;
    res = fscanf(f, "%s", wsk->type);
    if (res != 1)
    {
        if (err_code != NULL)
            *err_code = FILE_CORRUPTED;
        return fclose(f), free(wsk), NULL;
    }

    if (strcmp(wsk->type, "P2") != 0)
    {
        if (err_code != NULL)
            *err_code = FILE_CORRUPTED;
        return fclose(f), free(wsk), NULL;
    }

    res = fscanf(f, "%d %d", &wsk->width, &wsk->height);
    if (res != 2)
    {
        if (err_code != NULL)
            *err_code = FILE_CORRUPTED;
        return fclose(f), free(wsk), NULL;
    }
    if (wsk->width < 1 || wsk->height < 1)
    {
        if (err_code != NULL)
            *err_code = FILE_CORRUPTED;
        return fclose(f), free(wsk), NULL;
    }
    wsk->ptr = (int **)calloc(wsk->height, sizeof(int *));
    if (wsk->ptr == NULL)
    {
        if (err_code != NULL)
            *err_code = MEMORY_FAIL;
        return fclose(f), free(wsk), NULL;
    }
    for (int i = 0; i < wsk->height; i++)
    {
        *(wsk->ptr + i) = (int *)calloc(wsk->width, sizeof(int));
        if (*(wsk->ptr + i) == NULL)
        {
            if (err_code != NULL)
                *err_code = MEMORY_FAIL;
            return fclose(f), destroy_image(&wsk), NULL;
        }
    }
    int tmp;
    res = fscanf(f, "%d", &tmp);
    if (res != 1 || tmp > 255 || tmp < 0)
    {
        if (err_code != NULL)
            *err_code = FILE_CORRUPTED;
        return fclose(f), destroy_image(&wsk), NULL;
    }
    for (int i = 0; i < wsk->height; i++)
    {
        for (int j = 0; j < wsk->width; j++)
        {
            res = fscanf(f, "%d", (*(wsk->ptr + i) + j));
            if (res != 1 || *(*(wsk->ptr + i) + j) < 0 || *(*(wsk->ptr + i) + j) > 255 || *(*(wsk->ptr + i) + j) > tmp)
            {
                if (err_code != NULL)
                    *err_code = FILE_CORRUPTED;
                return fclose(f), destroy_image(&wsk), NULL;
            }
        }
    }

    if (err_code != NULL)
        *err_code = SUCCESS;
    fclose(f);
    return wsk;
}

int save_image_t(const char *filename, const struct image_t *m1)
{
    if (filename == NULL || m1 == NULL || m1->height < 1 || m1->width < 1 || m1->ptr == NULL)
        return INCORRECT_INPUT;

    FILE *f;
    f = fopen(filename, "w");
    if (f == NULL)
        return FILE_FAIL;

    fprintf(f, "%s\n", m1->type);
    fprintf(f, "%d %d\n", m1->width, m1->height);
    fprintf(f, "%d\n", 255);

    for (int i = 0; i < m1->height; i++)
    {
        for (int j = 0; j < m1->width; j++)
            fprintf(f, "%d ", *(*(m1->ptr + i) + j));
        fprintf(f, "\n");
    }

    fclose(f);
    return SUCCESS;
}

void destroy_image(struct image_t **m)
{
    if (m == NULL || *m == NULL)
        return;

    for (int i = 0; i < (*m)->height; i++)
        free(*((*m)->ptr + i));
    free((*m)->ptr);
    free(*m);
    *m = NULL;
}

struct image_t *image_flip_horizontal(const struct image_t *m1)
{
    if (m1 == NULL)
        return NULL;

    struct image_t *tmp = (struct image_t *)calloc(1, sizeof(struct image_t));
    if (tmp == NULL)
        return NULL;

    tmp->width = m1->width;
    tmp->height = m1->height;

    if (strcmp(m1->type, "P2") != 0)
        return free(tmp), NULL;
    
    strcpy(tmp->type, m1->type);

    if (tmp->width < 1 || tmp->height < 1)
        return free(tmp), NULL;

    tmp->ptr = (int **)calloc(tmp->height, sizeof(int *));
    if (tmp->ptr == NULL)
        return free(tmp), NULL;

    for (int i = 0; i < tmp->height; i++)
    {
        *(tmp->ptr + i) = (int *)calloc(tmp->width, sizeof(int));
        if (*(tmp->ptr + i) == NULL)
            return destroy_image(&tmp), NULL;
    }

    for (int i = 0; i < tmp->height; i++)
    {
        for (int j = 0; j < tmp->width; j++)
            *(*(tmp->ptr + i) + j) = *(*(m1->ptr + tmp->height - 1 - i) + j);
    }
    return tmp;
}

struct image_t *image_flip_vertical(const struct image_t *m1)
{
    if (m1 == NULL)
        return NULL;

    struct image_t *tmp = (struct image_t *)calloc(1, sizeof(struct image_t));
    if (tmp == NULL)
        return NULL;

    tmp->width = m1->width;
    tmp->height = m1->height;

    if (tmp->width < 1 || tmp->height < 1)
        return free(tmp), NULL;
    
    if (strcmp(m1->type, "P2") != 0)
        return free(tmp), NULL;
    
    strcpy(tmp->type, m1->type);

    tmp->ptr = (int **)calloc(tmp->height, sizeof(int *));
    if (tmp->ptr == NULL)
        return free(tmp), NULL;

    for (int i = 0; i < tmp->height; i++)
    {
        *(tmp->ptr + i) = (int *)calloc(tmp->width, sizeof(int));
        if (*(tmp->ptr + i) == NULL)
            return destroy_image(&tmp), NULL;
    }

    for (int i = 0; i < tmp->height; i++)
    {
        for (int j = 0; j < tmp->width; j++)
            *(*(tmp->ptr + i) + j) = *(*(m1->ptr + i) + tmp->width - 1 - j);
    }
    return tmp;
}

struct image_t *image_negate(const struct image_t *m1)
{
    if (m1 == NULL)
        return NULL;

    struct image_t *tmp = (struct image_t *)calloc(1, sizeof(struct image_t));
    if (tmp == NULL)
        return NULL;

    tmp->width = m1->width;
    tmp->height = m1->height;

    if (tmp->width < 1 || tmp->height < 1)
        return free(tmp), NULL;
    
    if (strcmp(m1->type, "P2") != 0)
        return free(tmp), NULL;
    
    strcpy(tmp->type, m1->type);

    tmp->ptr = (int **)calloc(tmp->height, sizeof(int *));
    if (tmp->ptr == NULL)
        return free(tmp), NULL;

    for (int i = 0; i < tmp->height; i++)
    {
        *(tmp->ptr + i) = (int *)calloc(tmp->width, sizeof(int));
        if (*(tmp->ptr + i) == NULL)
            return destroy_image(&tmp), NULL;
    }

    for (int i = 0; i < tmp->height; i++)
    {
        for (int j = 0; j < tmp->width; j++)
            *(*(tmp->ptr + i) + j) = 255 - *(*(m1->ptr + i) + j);
    }
    return tmp;
}