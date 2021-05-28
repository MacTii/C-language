#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define N 1000
#define N_RESULT 4004
#define COUNT 4

#define FAILED_TO_ALLOCATE_MEMORY 8
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2

char *concatenate(int count, ...)
{
	if (count < 1)
		return NULL;

	va_list ap;
	va_start(ap, count);
	char *first = va_arg(ap, char *);

	int first_len = strlen(first) + 1; // dlugosc pierwszego tekstu + 1(\0)

	char *res = (char *)calloc(first_len, sizeof(char));
	if (!res)
		return va_end(ap), NULL;

	strcpy(res, first);

	int len = first_len;
	for (int i = 0; i < count - 1; i++)
	{
		char *current = va_arg(ap, char *);

		int curr_len = strlen(current) + 1; // current dlugosc
		len += curr_len;					// size calego tekstu

		char *result = realloc(res, sizeof(char) * len);
		if (!result)
		{
			free(res);
			return va_end(ap), NULL;
		}

		res = result;

		strcat(res, " ");	  // laczenie tekstu i spacji
		strcat(res, current); // laczenie tekstu i tekstu
	}
	va_end(ap);
	return res;
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

	char *result = NULL;
	/*char* result = (char*)calloc(N_RESULT, sizeof(char));

    if (!result)
    {
        for (int i = 0; i < COUNT; i++)
            free(*(tab + i));

        free(tab);

        return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
    }*/

	int number;

	printf("Podaj liczbe tekstow do wprowadzenia: ");

	int error = scanf("%d", &number);
	if (error != 1)
	{
		for (int i = 0; i < COUNT; i++)
			free(*(tab + i));

		free(tab);
		//free(result);

		return printf("Incorrect input"), INCORRECT_INPUT;
	}

	if (number < 2 || number > 4)
	{
		for (int i = 0; i < COUNT; i++)
			free(*(tab + i));

		free(tab);
		//free(result);

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
		result = concatenate(2, *tab, *(tab + 1));
		break;
	case 3:
		result = concatenate(3, *tab, *(tab + 1), *(tab + 2));
		break;
	case 4:
		result = concatenate(4, *tab, *(tab + 1), *(tab + 2), *(tab + 3));
		break;
	default:
		break;
	}

	if (!result)
	{
		for (int j = 0; j < COUNT; j++)
			free(*(tab + j));

		free(tab);

		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	}

	printf("%s", result);

	for (int i = 0; i < 4; i++)
		free(*(tab + i));

	free(tab);
	free(result);

	return 0;
}