#include <stdio.h>
#include <stdlib.h>
#include "comparators.h"

#define SUCCESS 0
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8

int main()
{
	int error, type;
	printf("Enter data type: ");
	error = scanf("%d", &type);
	if (error != 1)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (type < 0 || type > 2)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	int size;
	printf("Enter array size: ");
	error = scanf("%d", &size);
	if (error != 1)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (size < 1)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	int *tab_int;
	double *tab_double;
	struct point_t *tab_point;
	int i;

	switch (type)
	{
	case 0:

		tab_int = (int *)calloc(size, sizeof(int));
		if (tab_int == NULL)
			return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

		printf("Enter ints: ");
		for (i = 0; i < size; i++)
		{
			error = scanf("%d", tab_int + i);
			if (!error)
				return printf("Incorrect input"), free(tab_int), INCORRECT_INPUT;
		}

		sort(tab_int, size, sizeof(int), comp_int);

		for (int i = 0; i < size; i++)
			printf("%d ", *(tab_int + i));

		free(tab_int);
		break;

	case 1:

		tab_double = (double *)calloc(size, sizeof(double));
		if (tab_double == NULL)
			return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

		printf("Enter doubles: ");
		for (i = 0; i < size; i++)
		{
			error = scanf("%lf", tab_double + i);
			if (error != 1)
				return printf("Incorrect input"), free(tab_double), INCORRECT_INPUT;
		}

		sort(tab_double, size, sizeof(double), comp_double);

		for (int i = 0; i < size; i++)
			printf("%lf ", *(tab_double + i));

		free(tab_double);
		break;

	case 2:

		tab_point = (struct point_t *)calloc(size, sizeof(struct point_t));
		if (tab_point == NULL)
			return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

		printf("Enter points: ");
		for (i = 0; i < size; i++)
		{
			error = scanf("%lf %lf", &(tab_point + i)->x, &(tab_point + i)->y);
			if (error != 2)
				return printf("Incorrect input"), free(tab_point), INCORRECT_INPUT;
		}

		sort(tab_point, size, sizeof(struct point_t), comp_point);

		for (int i = 0; i < size; i++)
			printf("%lf %lf\n", (tab_point + i)->x, (tab_point + i)->y);

		free(tab_point);
		break;

	default:
		break;
	}

	return SUCCESS;
}