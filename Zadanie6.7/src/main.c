#include "comparators.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8

#define COMPARATORS 3

//width wiersze
//height kolumny

int main()
{
	int error, width, height;
	printf("Enter width and height: ");
	error = scanf("%d %d", &width, &height);
	if (error != 2)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (width < 1 || height < 1)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	int **tab = (int **)calloc(height, sizeof(int *));
	if (tab == NULL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	for (int i = 0; i < height; i++)
	{
		*(tab + i) = calloc(width, sizeof(int));
		if (*(tab + i) == NULL)
		{
			for (int j = 0; j < i; j++)
				free(*(tab + j));
			return printf("Failed to allocate memory"), free(tab), FAILED_TO_ALLOCATE_MEMORY;
		}
	}

	printf("Enter data: ");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			error = scanf("%d", (*(tab + i) + j));
			if (error != 1)
			{
				for (int k = 0; k < height; k++)
					free(*(tab + k));
				return printf("Incorrect input"), free(tab), INCORRECT_INPUT;
			}
		}
	}

	int (**comparators)(const int *, const int *, int) = (int (**)(const int *, const int *, int))calloc(COMPARATORS, sizeof(int (*)(const int *, const int *, int)));
	if (comparators == NULL)
	{
		for (int i = 0; i < height; i++)
			free(*(tab + i));
		return printf("Failed to allocate memory"), free(tab), FAILED_TO_ALLOCATE_MEMORY;
	}

	*comparators = comp_min;
	*(comparators + 1) = comp_max;
	*(comparators + 2) = comp_sum;

	int op;
	printf("Selection choice: ");
	error = scanf("%d", &op);
	if (error != 1)
	{
		free(comparators);
		for (int i = 0; i < height; i++)
			free(*(tab + i));
		return printf("Incorrect input"), free(tab), INCORRECT_INPUT;
	}
	if (op < 0 || op > 2)
	{
		free(comparators);
		for (int i = 0; i < height; i++)
			free(*(tab + i));
		return printf("Incorrect input data"), free(tab), INCORRECT_INPUT_DATA;
	}

	switch (op)
	{
	case 0:
		sort_rows(tab, width, height, *comparators);
		break;

	case 1:
		sort_rows(tab, width, height, *(comparators + 1));
		break;

	case 2:
		sort_rows(tab, width, height, *(comparators + 2));
		break;

	default:
		break;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			printf("%d ", *(*(tab + i) + j));
		printf("\n");
	}

	free(comparators);
	for (int i = 0; i < height; i++)
		free(*(tab + i));
	free(tab);

	return SUCCESS;
}