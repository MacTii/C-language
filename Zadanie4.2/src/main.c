#include <stdio.h>
#include <stdlib.h>

#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8

void destroy_array_2d(int **ptr, int height)
{
	if (ptr == NULL || height <= 0)
		return;
	int i;
	for (i = 0; i < height; i++)
	{
		free(*(ptr + i));
	}
	free(ptr);
}

int **create_array_2d(int width, int height)
{
	if (width <= 0 || height <= 0)
		return NULL;
	int **ptr = (int **)malloc(sizeof(int *) * height);
	if (ptr == NULL)
		return NULL;
	int i;
	for (i = 0; i < height; i++)
	{
		*(ptr + i) = (int *)malloc(sizeof(int) * width);
		if (*(ptr + i) == NULL)
		{
			destroy_array_2d(ptr, height);
			return NULL;
		}
	}
	return ptr;
}

void display_array_2d(int **ptr, int width, int height)
{
	if (ptr == NULL || width <= 0 || height <= 0)
		return;
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
			printf("%d ", *(*(ptr + i) + j));
		printf("\n");
	}
}

int main()
{
	printf("Podaj szerokosc i wysokosc: ");
	int width, height;
	int x = scanf("%d %d", &width, &height);
	if (x != 2)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (width <= 0 || height <= 0)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;
	int **ptr = create_array_2d(width, height);
	if (ptr == NULL)
	{
		printf("Failed to allocate memory");
		return FAILED_TO_ALLOCATE_MEMORY;
	}
	printf("Podaj liczby:\n");
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
			x = scanf("%d", (*(ptr + i) + j));
		if (x != 1)
		{
			printf("Incorrect input");
			destroy_array_2d(ptr, height);
			return INCORRECT_INPUT;
		}
	}
	display_array_2d(ptr, width, height);
	destroy_array_2d(ptr, height);
	return 0;
}
