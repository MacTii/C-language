#include "format_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define WRONG_INPUT 1
#define NOT_EXIST 2
#define CORRUPTED 3
#define FAILED_MEMORY 4
#define SUCCESS 0
#define INCORRECT_DATA -1
#define MEMORY -2
#define UNSUPPORTED 7
#define IMPOSSIBLE_TO_OPEN 4
#define FILE_CORRUPTED 8
#define MEMORY_ERROR 8

struct statistic_t
{
	int min;
	int max;
	float avg;
	float standard_deviation;
	int range;
};

/*
int load(const char *filename, int ***ptr, enum save_format_t format);
int statistics_row(int **ptr, struct statistic_t **stats);
void destroy(int ***ptr);
void display(int **ptr);
*/

void destroy(int ***ptr)
{
	if (ptr && *ptr)
	{
		int i = 0;

		while (*(*ptr + i) != NULL)
		{
			free(*(*ptr + i));
			i++;
		}

		free(*ptr);
	}
}

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

//int file_size(FILE *f) //nie potrzeba
//{
//  if (!f) return -1;
//  int size;
//
//  fseek(f, 0, SEEK_END);
//  size = ftell(f);
//  fseek(f, 0, SEEK_SET);
//
//  return size;
//}

void display_stats(struct statistic_t **stats, int size) //nie potrzeba
{
	if (!stats)
		return;

	for (int i = 0; i < size; i++)
		printf("%d %d %d %f %f\n", (*(stats) + i)->min, (*(stats) + i)->max, (*(stats) + i)->range, (*(stats) + i)->avg, (*(stats) + i)->standard_deviation);
}

int load(const char *filename, int ***ptr, enum save_format_t format)
{
	if (!filename || !ptr || (format != fmt_text && format != fmt_binary))
		return WRONG_INPUT;

	if (format == fmt_binary)
	{
		FILE *file;
		int number = 1, count = 0, size, position, last, *ptr2 = &number;

		file = fopen(filename, "rb+");
		if (file == NULL)
			return NOT_EXIST;

		while (1)
		{
			fread(ptr2, sizeof(int), 1, file);
			if (feof(file))
				break;

			if (*ptr2 == -1)
				count += 1;
		}

		rewind(file);
		size = count + 1;

		if (!count)
			return fclose(file), CORRUPTED;

		*ptr = (int **)malloc(sizeof(int *) * size);
		if (!*ptr)
			return fclose(file), FAILED_MEMORY;

		for (int index = 0; index < count; ++index)
		{
			if (feof(file))
				break;

			size = 0;
			position = ftell(file);

			while (1)
			{
				fread(ptr2, sizeof(int), 1, file);
				size++;

				if (*ptr2 == -1)
					break;
			}

			fseek(file, position, 0);
			*(*ptr + index) = (int *)malloc(sizeof(int) * size);

			if (!*(*ptr + index))
				return destroy(ptr), fclose(file), FAILED_MEMORY;

			last = 0;
			while (1)
			{
				fread(*(*ptr + index) + last, sizeof(int), 1, file);
				if (*(*(*ptr + index) + last) == -1)
					break;

				last++;
			}
		}
		fclose(file);
	}
	else
	{
		FILE *file;
		int number, result, count = 0;
		file = fopen(filename, "r+");

		if (!file)
			return NOT_EXIST;

		while (1)
		{
			result = fscanf(file, "%d", &number);
			if (feof(file))
				break;

			if (result != 1)
				return fclose(file), CORRUPTED;

			if (number == -1)
				count += 1;
		}

		if (!count)
			return fclose(file), CORRUPTED;

		rewind(file);
		int size = count;
		count += 1;

		*ptr = (int **)calloc(count, sizeof(int *));
		if (!*ptr)
			return fclose(file), FAILED_MEMORY;

		for (int i = 0, j; i < size; i++)
		{

			if (feof(file))
				break;

			count = 0;
			int position = ftell(file);
			while (1)
			{
				fscanf(file, "%d", &number);
				count += 1;

				if (number == -1)
					break;
			}
			*(*ptr + i) = (int *)calloc(count, sizeof(int));

			if (*(*ptr + i) == NULL)
				return destroy(ptr), fclose(file), FAILED_MEMORY;

			j = 0;
			fseek(file, position, 0);
			while (1)
			{
				fscanf(file, "%d", *(*ptr + i) + j);
				if (*(*(*ptr + i) + j) == -1)
					break;

				else
					j += 1;
			}
		}
		fclose(file);
	}
	return SUCCESS;
}

int statistics_row(int **ptr, struct statistic_t **stats)
{
	if (!ptr || !stats)
		return -1;

	*stats = (struct statistic_t *)malloc(sizeof(struct statistic_t));

	if (!*stats)
		return -2;

	int i = 0,
		j = 0,
		count = 0,
		sum = 0;

	while (*(ptr + j) != NULL)
	{
		i = 0;
		count = 0;
		sum = 0;

		if (*ptr && **(ptr + j) != -1)
		{
			(*(stats) + j)->min = **(ptr + j);
			(*(stats) + j)->max = **(ptr + j);

			while (*(*(ptr + j) + i) != -1)
			{

				int current = *(*(ptr + j) + i);

				if (current < (*(stats) + j)->min)
					(*(stats) + j)->min = current;

				if (current > (*(stats) + j)->max)
					(*(stats) + j)->max = current;

				sum += current;
				i++;
				count++;
			}

			(*(stats) + j)->avg = (float)sum / count;
			(*(stats) + j)->range = abs((*(stats) + j)->max - (*(stats) + j)->min);

			float sd = 0;

			for (int k = 0; k < i; k++)
			{

				int current = *(*(ptr + j) + k);

				sd += pow(current - (*(stats) + j)->avg, 2);
			}

			(*(stats) + j)->standard_deviation = sqrt(sd / count);

			j++;
			*stats = (struct statistic_t *)realloc(*stats, sizeof(struct statistic_t) * (j + 1));

			if (!*stats)
				return 2;
		}

		else
		{
			(*(stats) + j)->min = -1;
			(*(stats) + j)->max = -1;
			(*(stats) + j)->avg = -1;
			(*(stats) + j)->standard_deviation = -1;
			(*(stats) + j)->range = -1;

			j++;
			*stats = (struct statistic_t *)realloc(*stats, sizeof(struct statistic_t) * (j + 1));

			if (!*stats)
				return 2;
		}
	}

	return j;
}

int main()
{
	char *filename = (char *)calloc(40, sizeof(char));
	struct statistic_t *stats;
	int **ptr;

	if (!filename)
		return printf("Failed to allocate memory\n"), 8;

	printf("Podaj nazwe pliku: ");
	scanf("%39s", filename);

	int size = strlen(filename);
	if (*(filename + size - 1) == 'n' && *(filename + size - 2) == 'i' && *(filename + size - 3) == 'b' && *(filename + size - 4) == '.')
	{
		int spr = load(filename, &ptr, fmt_binary);
		if (spr == 2)
			return free(filename), printf("Couldn't open file\n"), 4;

		else if (spr == 3)
			return free(filename), printf("File corrupted\n"), 6;

		else if (spr == 4)
			return printf("Failed to allocate memory\n"), free(filename), 8;
	}
	else if (*(filename + size - 1) == 't' && *(filename + size - 2) == 'x' && *(filename + size - 3) == 't' && *(filename + size - 4) == '.')
	{
		int spr = load(filename, &ptr, fmt_text);

		if (spr == 2)
			return free(filename), printf("Couldn't open file\n"), 4;
		else if (spr == 3)
			return free(filename), printf("File corrupted\n"), 6;

		else if (spr == 4)
			return free(filename), printf("Failed to allocate memory\n"), 8;
	}
	else
		return printf("Unsupported file format\n"), free(filename), 7;

	int size1 = statistics_row(ptr, &stats);
	if (size1 == -2)
		return printf("Failed to allocate memory\n"), destroy(&ptr), free(filename), 8;

	display_stats(&stats, size1);

	free(filename);
	free(stats);
	destroy(&ptr);

	return 0;
}