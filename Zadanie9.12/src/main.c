#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8
#define FAILED_MEMORY 2
#define NOT_ENOUGH_DATA_AVAILABLE 3

int main()
{
	struct doubly_linked_list_t *dll = dll_create();
	if (!dll)
		return printf("Failed to allocate memory\n"), FAILED_TO_ALLOCATE_MEMORY;
	int val, check, choice, check_sum = 0;

	printf("Enter list (-1 when done): ");
	while (1)
	{
		check = scanf("%d", &val);
		if (check != 1)
		{
			dll_clear(dll);
			free(dll);
			return printf("Incorrect input\n"), INCORRECT_INPUT;
		}

		if (val == -1)
			break;

		check = dll_push_back(dll, val);
		if (check == FAILED_MEMORY)
		{
			dll_clear(dll);
			free(dll);
			return printf("Failed to allocate memory\n"), FAILED_TO_ALLOCATE_MEMORY;
		}
		check_sum++;
	}

	if (check_sum == 0)
	{
		dll_clear(dll);
		free(dll);
		return printf("Not enough data available\n"), NOT_ENOUGH_DATA_AVAILABLE;
	}

	printf("Choose sorting (0 or 1): ");
	check = scanf("%d", &choice);
	if (check != 1)
	{
		dll_clear(dll);
		free(dll);
		return printf("Incorrect input\n"), INCORRECT_INPUT;
	}
	if (choice != 0 && choice != 1)
	{
		dll_clear(dll);
		free(dll);
		return printf("Incorrect input data\n"), INCORRECT_INPUT_DATA;
	}

	switch (choice)
	{
	case 0:
		dll_sort_asc(dll);
		dll_display(dll);
		printf("\n");
		dll_display_reverse(dll);
		printf("\n");
		break;
	case 1:
		dll_sort_desc(dll);
		dll_display(dll);
		printf("\n");
		dll_display_reverse(dll);
		printf("\n");
		break;
	}
	dll_clear(dll);
	free(dll);
	return 0;
}