#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "format_type.h"
#include <string.h>

struct statistic_t
{
	int min;
	int max;
	float avg;
	float standard_deviation;
	int range;
};

int statistics(int **ptr, struct statistic_t **stats)
{
	if (ptr == NULL || stats == NULL)
		return 1;
	*stats = (struct statistic_t *)malloc(sizeof(struct statistic_t));
	if (*stats == NULL)
		return 2;
	if (*ptr != NULL && **ptr != -1)
	{
		(*stats)->min = **ptr;
		(*stats)->max = **ptr;
	}
	int i, j, suma = 0, n = 0;
	for (i = 0; *(ptr + i) != NULL; i++)
	{
		for (j = 0; *(*(ptr + i) + j) != -1; j++)
		{
			int number = *(*(ptr + i) + j);
			if (number < (*stats)->min)
				(*stats)->min = number;
			if (number > (*stats)->max)
				(*stats)->max = number;
			suma += number;
			n++;
		}
	}
	if (!n)
	{
		free(*stats);
		return 3;
	}
	(*stats)->avg = (float)suma / n;
	(*stats)->range = abs((*stats)->max - (*stats)->min);
	float sr = 0;
	for (i = 0; *(ptr + i) != NULL; i++)
	{
		for (j = 0; *(*(ptr + i) + j) != -1; j++)
		{
			int number = *(*(ptr + i) + j);
			sr += pow(number - (*stats)->avg, 2);
		}
	}
	(*stats)->standard_deviation = sqrt(sr / n);
	return 0;
}

void display(int **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return;
	int i, j;
	for (i = 0; *(ptr + i) != NULL; i++)
	{
		for (j = 0; *(*(ptr + i) + j) != -1; j++)
			printf("%d ", *(*(ptr + i) + j));
		printf("\n");
	}
}

int save(const char *filename, int **ptr, enum save_format_t format)
{
	if (filename == NULL || ptr == NULL || (format != fmt_text && format != fmt_binary))
		return 1;
	if (format == fmt_text)
	{
		FILE *file;
		file = fopen(filename, "w+");
		if (file == NULL)
			return 2;
		int i, k;
		for (i = 0, k = 0; *(ptr + k) != NULL; i++)
		{
			if (*(*(ptr + k) + i) != -1)
				fprintf(file, "%d ", *(*(ptr + k) + i));
			else
			{
				fprintf(file, "%d\n", -1);
				i = -1;
				k++;
			}
		}
		fclose(file);
	}
	else
	{
		FILE *file;
		file = fopen(filename, "wb+");
		if (file == NULL)
			return 2;
		int elements, k;
		for (elements = 0, k = 0; *(ptr + elements) != NULL; k++)
		{
			if (*(*(ptr + elements) + k) == -1)
			{
				fwrite(*(ptr + elements), sizeof(int), ++k, file);
				elements++;
				k = -1;
			}
		}
		fclose(file);
	}
	return 0;
}

int main()
{
	int A[] = {10, 20, 30, 40, 50, 60, 70, -1};
	int B[] = {100, 200, 300, 400, 500, 600, 700, 800, -1};
	int C[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, -1};
	int *D[] = {A, B, C, NULL};
	struct statistic_t *stats;
	display(D);
	char *filename = (char *)malloc(sizeof(char) * 40);
	if (filename == NULL)
		return printf("Failed to allocate memory"), 8;
	printf("Podaj nazwe pliku: ");
	scanf("%39s", filename);
	char *txt_filename = (char *)malloc(sizeof(char) * 44);
	if (txt_filename == NULL)
	{
		free(filename);
		printf("Failed to allocate memory");
		return 8;
	}
	char *bin_filename = (char *)malloc(sizeof(char) * 44);
	if (bin_filename == NULL)
	{
		free(filename);
		free(txt_filename);
		printf("Failed to allocate memory");
		return 8;
	}
	strcpy(txt_filename, filename);
	strcpy(bin_filename, filename);
	if (!!save(strcat(txt_filename, ".txt"), D, fmt_text))
		printf("Couldn't create file\n");
	else
		printf("File saved\n");
	if (!!save(strcat(bin_filename, ".bin"), D, fmt_binary))
		printf("Couldn't create file\n");
	else
		printf("File saved\n");
	int x = statistics(D, &stats);
	if (x == 2)
	{
		free(filename);
		free(txt_filename);
		free(bin_filename);
		printf("Failed to allocate memory");
		return 8;
	}
	if (x == 3)
		printf("Not enough data");
	printf("%d\n%d\n%d\n%f\n%f", stats->min, stats->max, stats->range, stats->avg, stats->standard_deviation);
	free(filename);
	free(txt_filename);
	free(bin_filename);
	free(stats);
	return 0;
}