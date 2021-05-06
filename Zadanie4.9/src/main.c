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

	printf("Enter destination image file name: ");
	scanf("%39s", filename);

	while (getchar() != '\n')
		;

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

	int count;
	printf("How many subimages you want to draw: ");
	if (scanf("%d", &count) != 1)
		return printf("Incorrect input"), free(filename), destroy_image(&img), INCORRECT_INPUT;

	if (count < 1)
		return printf("Incorrect input data"), free(filename), destroy_image(&img), INCORRECT_INPUT_DATA;

	char *image = NULL;
	struct image_t *source = NULL;

	for (int i = 0; i < count; i++)
	{
		image = (char *)calloc(SIZE, sizeof(char));
		if (image == NULL)
			return printf("Failed to allocate memory"), free(filename), destroy_image(&img), FAILED_TO_ALLOCATE_MEMORY;

		printf("Enter a name of a subimage: ");
		scanf("%38s", image);

		while (getchar() != '\n')
			;

		source = load_image_t(image, &error);
		if (error == 2)
		{
			printf("Couldn't open file\n");
			free(image);
			destroy_image(&source);
			continue;
		}
		else if (error == 1 || error == 3)
		{
			printf("File corrupted\n");
			free(image);
			destroy_image(&source);
			continue;
		}
		else if (error == 4)
			return free(filename), destroy_image(&img), destroy_image(&source), free(image), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

		int x, y;
		printf("Enter coordinates (x, y): ");
		if (scanf("%d %d", &x, &y) != 2)
			return printf("Incorrect input"), free(filename), destroy_image(&img), destroy_image(&source), free(image), INCORRECT_INPUT;

		else if (draw_image(img, source, x, y) != 0)
		{
			printf("Incorrect input data\n");
			free(image);
			destroy_image(&source);
			continue;
		}
		free(image);
		destroy_image(&source);
	}

	char *temp = (char *)malloc((SIZE + 9) * sizeof(char)); // na.jpg.txt
	if (temp == NULL)
		return free(filename), destroy_image(&img), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	int len = strlen(filename);
	*(filename + len - 4) = '\0';
	sprintf(temp, "%s_modified.%s", filename, filename + len - 3);

	int err = save_image_t(temp, img);
	if (err != 0)
		return printf("Couldn't create file"), free(filename), destroy_image(&img), free(temp), COULDNT_CREATE_FILE;

	printf("File saved\n");

	free(filename);
	destroy_image(&img);
	free(temp);

	return 0;
}