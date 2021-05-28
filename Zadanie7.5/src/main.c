#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define N 1000
#define FAILED_TO_ALLOCATE_MEMORY 8
#define WSK_FUNCTIONS 4
#define INT_OPTIONS 4
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define SUCCESS 0

int main()
{
	char *text_input = (char *)calloc(N + 1, sizeof(char));
	if (!text_input)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	typedef char *(*fun)(const char *);

	fun *wsk = (fun *)calloc(WSK_FUNCTIONS, sizeof(fun));
	if (!wsk)
	{
		free(text_input);
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	}

	int *choice = (int *)calloc(INT_OPTIONS, sizeof(int));
	if (!choice)
	{
		free(text_input);
		free(wsk);
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	}

	printf("Podaj tekst do przeksztalcenia: ");
	scanf("%1000[^\n]s", text_input);

	while (getchar() != '\n')
		;

	printf("Podaj liczbe operacji do przeprowadzenia: ");
	int count_op, error;
	error = scanf("%d", &count_op);
	if (error != 1)
	{
		free(text_input);
		free(wsk);
		free(choice);
		return printf("Incorrect input"), INCORRECT_INPUT;
	}

	if (count_op < 2 || count_op > 4)
	{
		free(text_input);
		free(wsk);
		free(choice);
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;
	}

	printf("Podaj wybrane operacje: ");
	for (int i = 0; i < count_op; i++)
	{
		error = scanf("%d", (choice + i));
		if (error != 1)
		{
			free(text_input);
			free(wsk);
			free(choice);
			return printf("Incorrect input"), INCORRECT_INPUT;
		}
	}

	*wsk = lower_to_upper;
	*(wsk + 1) = upper_to_lower;
	*(wsk + 2) = reverse_letter;
	*(wsk + 3) = space_to_dash;

	char **result;
	switch (count_op)
	{
	case 2:
		result = text_modifier(text_input, 2, *(wsk + *choice), *(wsk + *(choice + 1)));
		break;
	case 3:
		result = text_modifier(text_input, 3, *(wsk + *choice), *(wsk + *(choice + 1)), *(wsk + *(choice + 2)));
		break;
	case 4:
		result = text_modifier(text_input, 4, *(wsk + *choice), *(wsk + *(choice + 1)), *(wsk + *(choice + 2)), *(wsk + *(choice + 3)));
		break;
	default:
		free(text_input);
		free(wsk);
		free(choice);
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;
	}

	if (!result)
	{
		free(text_input);
		free(wsk);
		free(choice);
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	}

	for (int i = 0; *(result + i); i++)
		printf("%s\n", *(result + i));

	free(text_input);
	free(wsk);
	free(choice);
	free_texts(result);

	return SUCCESS;
}