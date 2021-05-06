#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils.h"

#define FAILED_TO_ALLOCATE_MEMORY 8
#define COULDNT_OPEN_FILE 4
#define FILE_CORRUPTED 6
#define SIZE 39

int main()
{
	char *filename = (char *)malloc((SIZE + 1) * sizeof(char));
	if (filename == NULL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("Enter file name: ");
	scanf("%39s", filename);

	int error;
	struct image_t *img = load_image_t(filename, &error);
	if (error == 2)
		return free(filename), printf("Couldn't open file"), COULDNT_OPEN_FILE;
	else if (error == 1 || error == 3)
		return free(filename), destroy_image(&img), printf("File corrupted"), FILE_CORRUPTED;
	else if (error == 4)
		return free(filename), destroy_image(&img), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	struct image_t *tmp_h, *tmp_v, *tmp_n;
	tmp_v = image_flip_vertical(img);
	if (tmp_v == NULL)
		return free(filename), destroy_image(&img), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	char *temp = (char *)malloc(50 * sizeof(char));
	if (temp == NULL)
		return free(filename), destroy_image(&img), destroy_image(&tmp_v), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	strcpy(temp, "mirror_v_");
	strcat(temp, filename);

	int err = save_image_t(temp, tmp_v);
	if (err != 0)
		printf("Couldn't create file\n");
	else
		printf("File saved\n");

	tmp_h = image_flip_horizontal(img);
	if (tmp_h == NULL)
		return free(filename), destroy_image(&img), destroy_image(&tmp_v), free(temp), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	strcpy(temp, "mirror_h_");
	strcat(temp, filename);

	err = save_image_t(temp, tmp_h);
	if (err != 0)
		printf("Couldn't create file\n");
	else
		printf("File saved\n");

	tmp_n = image_negate(img);
	if (tmp_n == NULL)
		return free(filename), destroy_image(&img), destroy_image(&tmp_v), destroy_image(&tmp_h), free(temp), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	strcpy(temp, "invert_");
	strcat(temp, filename);

	err = save_image_t(temp, tmp_n);
	if (err != 0)
		printf("Couldn't create file\n");
	else
		printf("File saved\n");

	free(filename);
	destroy_image(&img);
	destroy_image(&tmp_h);
	destroy_image(&tmp_v);
	destroy_image(&tmp_n);
	free(temp);

	return 0;
}