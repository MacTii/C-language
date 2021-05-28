#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define SUCCESS 0
#define ERROR 1
#define FILE_ERROR 2
#define ALLOCATE_ERROR 3
#define FAIL -1
#define NOT_ENOUGH_ARGUMENTS 9
#define FAILED_TO_ALLOCATE_MEMORY 8
#define COULDNT_OPEN_FILE 4

int word_in_file(FILE *f, char *word)
{
	if (!f || !word)
		return FAIL;

	fseek(f, 0, SEEK_SET);

	int count = 0, check = false, check2 = true, check3 = false;
	while (!feof(f))
	{
		char c = fgetc(f);
		if (check3 && !isalpha(c)) // musza byc przynajmniej 2 litery
			count++;
		if (check && !isalpha(c)) // 1 litera
			count++;
		check3 = false;
		check = false;
		if (*word == c && check2)
		{
			for (int i = 1; i < (int)strlen(word); i++) // musza byc przynajmniej 2 litery
			{
				c = fgetc(f);
				if (c == EOF)
					break;
				if (*(word + i) != c)
					break;
				if (*(word + i) == c && i == (int)strlen(word) - 1)
					check3 = true;
			}
			if (check2 && (int)strlen(word) == 1) // 1 litera
				check = true;
		}
		if (*word != c)
			check2 = false;
		if (!isalpha(c))
			check2 = true;
	}
	return count;
}

int *count_words(const char *filename, int *err_code, int N, ...)
{
	if (!filename || N < 1)
	{
		if (err_code)
			*err_code = ERROR;
		return NULL;
	}

	int *counts = (int *)calloc(N, sizeof(int));
	if (!counts)
	{
		if (err_code)
			*err_code = ALLOCATE_ERROR;
		return NULL;
	}

	FILE *f;
	f = fopen(filename, "r");
	if (!f)
	{
		if (err_code)
			*err_code = FILE_ERROR;
		return free(counts), NULL;
	}

	va_list ap;
	va_start(ap, N);

	for (int i = 0; i < N; i++)
	{
		int count = 0;
		char *current = va_arg(ap, char *);
		count = word_in_file(f, current);
		*(counts + i) = count;
	}

	fclose(f);
	va_end(ap);

	if (err_code)
		*err_code = SUCCESS;
	return counts;
}

int main(int argc, char **argv)
{
	if (argc < 3)
		return printf("Not enough arguments"), NOT_ENOUGH_ARGUMENTS;

	int error;
	for (int i = 2; i < argc; i++)
	{
		int *res = count_words(*(argv + 1), &error, 1, *(argv + i));

		if (error == FILE_ERROR)
			return printf("Couldn't open file"), COULDNT_OPEN_FILE;
		else if (error == ALLOCATE_ERROR)
			return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

		if (res)
			printf("%d\n", *res);

		free(res);
	}

	return SUCCESS;
}