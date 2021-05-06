#include "image_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

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

const int *image_get_pixel(const struct image_t *img, int x, int y)
{
    if (img == NULL || img->ptr == NULL || img->height < 1 || img->width < 1 || x < 0 || y < 0 || img->height <= y || img->width <= x)
        return NULL;

    return *(img->ptr + y) + x;
}

int *image_set_pixel(struct image_t *img, int x, int y)
{
    return (int *)image_get_pixel(img, x, y);
}

int image_draw_rectangle(struct image_t *img, const struct rectangle_t *rect, int value)
{
    if (img == NULL || img->ptr == NULL || img->width < 1 || img->height < 1 || rect == NULL || rect->p.x < 0 || rect->p.y < 0 ||
        rect->height < 1 || rect->width < 1 || rect->p.x >= img->width || rect->p.y >= img->height || value < 0 || value > 255 ||
        rect->height + rect->p.y > img->height || rect->width + rect->p.x > img->width)
        return INCORRECT_INPUT;

    for (int i = rect->p.x; i < rect->p.x + rect->width; i++) //width = 8 x = 0
    {
        if (i == img->width)
            break;
        *(*(img->ptr + rect->p.y) + i) = value; // (ptr + 13) + 0 = 114
        *(*(img->ptr + rect->p.y + rect->height - 1) + i) = value; // (ptr + 5 + 5 - 1) + 0 = 114
    }
    for (int i = rect->p.y; i < rect->p.y + rect->height; i++) //height = 35 y = 5
    {
        if (i == img->height)
            break;
        *(*(img->ptr + i) + rect->p.x) = value; // (ptr + 0) + 25 = 114
        *(*(img->ptr + i) + rect->p.x + rect->width - 1) = value; // (ptr + 0) + 25 + 1 - 1 = 114
    }

    return SUCCESS;
}