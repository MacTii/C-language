#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#define SUCCESS 0
#define FAIL 1
#define FILE_FAIL 2
#define INCORRECT_FAIL 3
#define ALLOCATE_FAIL 4

#include <stdlib.h>

#define DEFINE_ARRAY(TYPE)  \
    struct array_##TYPE##_t \
    {                       \
        int size;           \
        int capacity;       \
        TYPE *data;         \
    };

#define CREATE_ARRAY(TYPE)                                                                                      \
    struct array_##TYPE##_t *create_array_##TYPE(int size)                                                      \
    {                                                                                                           \
        if (size < 1)                                                                                           \
            return NULL;                                                                                        \
                                                                                                                \
        struct array_##TYPE##_t *array = (struct array_##TYPE##_t *)calloc(1, sizeof(struct array_##TYPE##_t)); \
        if (!array)                                                                                             \
            return NULL;                                                                                        \
                                                                                                                \
        array->data = (TYPE *)calloc(size, sizeof(TYPE));                                                       \
        if (!array->data)                                                                                       \
            return free(array), NULL;                                                                           \
                                                                                                                \
        array->size = 0;                                                                                        \
        array->capacity = size;                                                                                 \
                                                                                                                \
        return array;                                                                                           \
    }

#define FREE_ARRAY(TYPE)                                   \
    void free_array_##TYPE(struct array_##TYPE##_t *array) \
    {                                                      \
        if (!array || !array->data)                        \
            return;                                        \
        free(array->data);                                 \
        free(array);                                       \
    }

#define SAVE_ARRAY(TYPE)                                                                                                    \
    int save_array_##TYPE(const struct array_##TYPE##_t *array, const char *filename)                                       \
    {                                                                                                                       \
        if (!array || !filename || !array->data || array->size < 1 || array->capacity < 1 || array->size > array->capacity) \
            return FAIL;                                                                                                    \
                                                                                                                            \
        FILE *f = fopen(filename, "wb");                                                                                    \
        if (!f)                                                                                                             \
            return FILE_FAIL;                                                                                               \
                                                                                                                            \
        fwrite(&(array->size), sizeof(int), 1, f);                                                                          \
        fwrite(array->data, sizeof(TYPE), array->size, f);                                                                  \
                                                                                                                            \
        fclose(f);                                                                                                          \
        return SUCCESS;                                                                                                     \
    }

#define LOAD_ARRAY(TYPE)                                                                \
    int load_array_##TYPE(struct array_##TYPE##_t **array, const char *filename)        \
    {                                                                                   \
        if (!array || !filename)                                                        \
            return FAIL;                                                                \
                                                                                        \
        FILE *f = fopen(filename, "rb");                                                \
        if (!f)                                                                         \
            return FILE_FAIL;                                                           \
                                                                                        \
        *array = (struct array_##TYPE##_t *)calloc(1, sizeof(struct array_##TYPE##_t)); \
        if (!*array)                                                                    \
            return fclose(f), ALLOCATE_FAIL;                                            \
                                                                                        \
        int size;                                                                       \
        size_t x = fread(&size, sizeof(int), 1, f);                                     \
        if (!x || size < 1)                                                             \
            return fclose(f), free(*array), INCORRECT_FAIL;                             \
                                                                                        \
        (*array)->size = size;                                                          \
        (*array)->capacity = size;                                                      \
                                                                                        \
        (*array)->data = (TYPE *)calloc(size, sizeof(TYPE));                            \
        if (!(*array)->data)                                                            \
            return fclose(f), free(*array), ALLOCATE_FAIL;                              \
                                                                                        \
        x = fread((*array)->data, sizeof(TYPE), (*array)->size, f);                     \
        if (x != (size_t)size)                                                          \
            return fclose(f), free(*array), free((*array)->data), INCORRECT_FAIL;       \
                                                                                        \
        fclose(f);                                                                      \
        return SUCCESS;                                                                 \
    }

#define SORT_ARRAY(TYPE)                                                                                       \
    int sort_array_##TYPE(struct array_##TYPE##_t *array)                                                      \
    {                                                                                                          \
        if (!array || !array->data || array->size < 1 || array->capacity < 1 || array->size > array->capacity) \
            return FAIL;                                                                                       \
                                                                                                               \
        for (int i = 0; i < array->size; i++)                                                                  \
        {                                                                                                      \
            for (int j = 0; j < array->size - 1; j++)                                                          \
            {                                                                                                  \
                if (*(array->data + j) > *(array->data + j + 1))                                               \
                {                                                                                              \
                    TYPE tmp = *(array->data + j);                                                             \
                    *(array->data + j) = *(array->data + j + 1);                                               \
                    *(array->data + j + 1) = tmp;                                                              \
                }                                                                                              \
            }                                                                                                  \
        }                                                                                                      \
        return SUCCESS;                                                                                        \
    }

#endif // !__FUNCTIONS_H__