#include <stdio.h>
#include <stdlib.h>

#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_V2 -1
#define FAIL_MEMORY 2
#define SUCCESS 0
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8

int create_array_2d_2(int ***ptr, int width, int height)
{
	if (ptr == NULL || width < 1 || height < 1)
		return INCORRECT_INPUT;

	*ptr = (int **)calloc(height, sizeof(int *));
	if (*ptr == NULL)
		return FAIL_MEMORY;

	for (int i = 0; i < height; i++)
	{
		*(*ptr + i) = (int *)calloc(width, sizeof(int));
		if (*(*ptr + i) == NULL)
		{
			for (int j = 0; j < i; j++)
				free(*(*ptr + j));
			return free(*ptr), FAIL_MEMORY;
		}
	}

	return SUCCESS;
}

void destroy_array_2d(int ***ptr, int height)
{
	if (ptr == NULL || height < 1)
		return;

	for (int i = 0; i < height; i++)
		free(*(*ptr + i));
	free(*ptr);
	*ptr = NULL;
}

void display_array_2d(int **ptr, int width, int height)
{
	if (ptr == NULL || width < 1 || height < 1)
		return;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			printf("%d ", *(*(ptr + i) + j));
		printf("\n");
	}
}

int sum_array_2d(int **ptr, int width, int height)
{
	if (ptr == NULL || width < 1 || height < 1)
		return INCORRECT_INPUT_V2;

	int sum = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			sum += *(*(ptr + i) + j);
	}
	return sum;
}

int sum_row(int *ptr, int width)
{
	if (ptr == NULL || width < 1)
		return INCORRECT_INPUT_V2;

	int sum = 0;
	for (int i = 0; i < width; i++)
		sum += *(ptr + i);

	return sum;
}

int main()
{
	int w, h;
	printf("Podaj szerokosc i wysokosc: ");
	if (scanf("%d %d", &w, &h) != 2)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (w < 1 || h < 1)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	int **tab;
	int err = create_array_2d_2(&tab, w, h);
	if (err == FAIL_MEMORY)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("Podaj liczby: ");
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			if (scanf("%d", *(tab + i) + j) != 1)
				return destroy_array_2d(&tab, h), printf("Incorrect input"), INCORRECT_INPUT;
	}

	display_array_2d(tab, w, h);

	for (int i = 0; i < h; i++)
		printf("%d\n", sum_row(*(tab + i), w));

	printf("%d", sum_array_2d(tab, w, h));

	destroy_array_2d(&tab, h);

	return SUCCESS;
}
