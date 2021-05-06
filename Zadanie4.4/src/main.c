#include <stdio.h>
#include <stdlib.h>

#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8

struct matrix_t
{
	int **ptr;
	int width;
	int height;
};

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

int main()
{
	struct matrix_t macierz;
	int width, height;
	printf("Podaj szerokosc i wysokosc: ");
	int x = scanf("%d %d", &width, &height);
	if (x != 2)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (width <= 0 || height <= 0)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;
	int control = matrix_create(&macierz, width, height);
	if (control == 2)
	{
		printf("Failed to allocate memory");
		return FAILED_TO_ALLOCATE_MEMORY;
	}
	printf("Podaj wartosci:\n");
	control = matrix_read(&macierz);
	if (control == 2)
	{
		printf("Incorrect input");
		matrix_destroy(&macierz);
		return INCORRECT_INPUT;
	}
	matrix_display(&macierz);
	matrix_destroy(&macierz);
}