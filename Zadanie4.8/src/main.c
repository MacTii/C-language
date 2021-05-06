#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils.h"

#define FAILED_TO_ALLOCATE_MEMORY 8
#define COULDNT_OPEN_FILE 4
#define FILE_CORRUPTED 6
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define COULDNT_CREATE_FILE 5
#define SIZE 39

int main()
{
    char *filename = (char *)calloc(SIZE + 1, sizeof(char));
    if (filename == NULL)
        return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

    printf("Enter file name: ");
    scanf("%39s", filename);

    while(getchar()!='\n');

    // int i;
    // for (i = 0; i < SIZE; i++)
    // {
    //     scanf("%c", filename + i);
    //     if (*(filename + i) == '\n')
    //     {
    //         *(filename + i) = '\0';
    //         break;
    //     }
    // }
    // if (*(filename + i - 1) != 't' && *(filename + i - 2) != 'x' && *(filename + i - 3) != 't')
    //     return printf("Incorrect input"), free(filename), INCORRECT_INPUT;

    int error;
    struct image_t *img = load_image_t(filename, &error);
    if (error == 2)
        return free(filename), printf("Couldn't open file"), COULDNT_OPEN_FILE;
    else if (error == 1 || error == 3)
        return free(filename), destroy_image(&img), printf("File corrupted"), FILE_CORRUPTED;
    else if (error == 4)
        return free(filename), destroy_image(&img), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

    struct rectangle_t *r = (struct rectangle_t *)calloc(1, sizeof(struct rectangle_t));
    if (r == NULL)
        return printf("Failed to allocate memory"), free(filename), destroy_image(&img), FAILED_TO_ALLOCATE_MEMORY;

    printf("Podaj wspolrzedne i wymiary prostokata: ");
    if (scanf("%d %d %d %d", &r->p.x, &r->p.y, &r->width, &r->height) != 4)
        return printf("Incorrect input"), free(r), free(filename), destroy_image(&img), INCORRECT_INPUT;

    int color;
    printf("Podaj kolor: ");
    if (scanf("%d", &color) != 1)
        return printf("Incorrect input"), free(r), free(filename), destroy_image(&img), INCORRECT_INPUT;

    if (color < 0 || color > 255 || r->p.x < 0 || r->p.y < 0 || r->height < 1 || r->width < 1 || r->p.x >= img->width || r->p.y >= img->height || r->height + r->p.y > img->height || r->width + r->p.x > img->width)
        return printf("Incorrect input data"), free(r), free(filename), destroy_image(&img), INCORRECT_INPUT_DATA;

    int err = image_draw_rectangle(img, r, color);
    if (err == 1)
        return printf("Couldn't create file"), free(r), free(filename), destroy_image(&img), COULDNT_CREATE_FILE;

    err = save_image_t(filename, img);
    if (err != 0)
        return printf("Couldn't create file"), free(r), free(filename), destroy_image(&img), COULDNT_CREATE_FILE;

    printf("File saved\n");

    free(filename);
    destroy_image(&img);
    free(r);

    return 0;
}