#include <stdio.h>
#include <stdlib.h>

#define N 10
#define FAILED_TO_ALLOCATE_MEMORY 8
#define SUCCESS 0

int main()
{
	int **tab = (int **)calloc(N, sizeof(int *));
	if (tab == NULL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	for (int i = 0; i < N; i++)
	{
		*(tab + i) = (int *)calloc(N, sizeof(int));
		if (*(tab + i) == NULL)
		{
			for (int j = 0; j < i; j++)
				free(*(tab + j));
			return free(tab), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			*(*(tab + i) + j) = (i+1) * (j+1);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%3d ", *(*(tab + i) + j));
		printf("\n");
	}

	for (int i = 0; i < N; i++)
		free(*(tab + i));
	free(tab);

	return SUCCESS;
}