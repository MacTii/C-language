#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define SUCCESS 0
#define FAIL 1
#define BUFF_FULL 2
#define N 1000
#define N_RESULT 4004
#define COUNT 4

#define FAILED_TO_ALLOCATE_MEMORY 8
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2

int concatenate(char *res, int size, int count, ...)
{
	if (!res || size < 1 || count < 1)
		return FAIL;

	va_list ap;
	va_start(ap, count);
	char *first = va_arg(ap, char *);

	int first_len = strlen(first) + 1; // dlugosc pierwszego tekstu + 1(\0)
	if (first_len > size)
		return va_end(ap), BUFF_FULL;

	strcpy(res, first);
	int len = first_len;

	for (int i = 0; i < count - 1; i++)
	{
		char *current = va_arg(ap, char *);
		int curr_len = strlen(current) + 1;
		if (size < curr_len + len)
			return va_end(ap), BUFF_FULL; // dlugosc 2 tekstow gdzie \0 + \0 -> ' ' \0
		strcat(res, " ");				  // laczenie tekstu i spacji
		strcat(res, current);			  // laczenie tekstu i tekstu
		len += curr_len;				  // sumowanie dlugosci tekstow
	}
	va_end(ap);
	return SUCCESS;
}

int main()
{
	char **tab = (char **)calloc(COUNT, sizeof(char *));

	if (!tab)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	for (int i = 0; i < COUNT; i++)
	{
		*(tab + i) = (char *)calloc(N + 1, sizeof(char));

		if (!*(tab + i))
		{
			for (int j = 0; j < i; j++)
				free(*(tab + j));

			free(tab);
			return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
		}
	}

	char *result = (char *)calloc(N_RESULT, sizeof(char));

	if (!result)
	{
		for (int i = 0; i < COUNT; i++)
			free(*(tab + i));

		free(tab);

		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	}

	int number;

	printf("Podaj liczbe tekstow do wprowadzenia: ");

	int error = scanf("%d", &number);
	if (error != 1)
	{
		for (int i = 0; i < COUNT; i++)
			free(*(tab + i));

		free(tab);
		free(result);

		return printf("Incorrect input"), INCORRECT_INPUT;
	}

	if (number < 2 || number > 4)
	{
		for (int i = 0; i < COUNT; i++)
			free(*(tab + i));

		free(tab);
		free(result);

		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;
	}

	while (getchar() != '\n')
		;

	printf("Podaj teksty: ");
	for (int i = 0; i < number; i++)
	{
		scanf("%1000[^\n]s", *(tab + i));
		while (getchar() != '\n')
			;
	}

	switch (number)
	{
	case 2:
		concatenate(result, N_RESULT, 2, *tab, *(tab + 1));
		break;
	case 3:
		concatenate(result, N_RESULT, 3, *tab, *(tab + 1), *(tab + 2));
		break;
	case 4:
		concatenate(result, N_RESULT, 4, *tab, *(tab + 1), *(tab + 2), *(tab + 3));
		break;
	default:
		break;
	}

	printf("%s", result);

	for (int i = 0; i < 4; i++)
		free(*(tab + i));

	free(tab);
	free(result);

	return 0;
}