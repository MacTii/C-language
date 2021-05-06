#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8

int main()
{
	int buffer_size;
	printf("Podaj rozmiar bufora: ");
	int x = scanf("%d", &buffer_size);
	if (x != 1)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (buffer_size < 1)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;
	struct circular_buffer_t *buff;
	int y = circular_buffer_create_struct(&buff, buffer_size);
	if (y != 0)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	int check, war, err, val, spr;
	do
	{
		printf("Co chcesz zrobic? ");
		if (scanf("%d", &check) != 1)
		{
			printf("Incorrect input");
			circular_buffer_destroy_struct(&buff);
			return INCORRECT_INPUT;
		}
		switch (check)
		{
		case 0:
			circular_buffer_destroy_struct(&buff);
			break;
		case 1:
			printf("Podaj wartosc: ");
			if (scanf("%d", &war) != 1)
			{
				printf("Incorrect input");
				circular_buffer_destroy_struct(&buff);
				return INCORRECT_INPUT;
			}
			circular_buffer_push_back(buff, war);
			break;
		case 2:
			val = circular_buffer_pop_back(buff, &err);
			if (err == 2)
				printf("Buffer is empty\n");
			else
				printf("%d\n", val);
			break;
		case 3:
			val = circular_buffer_pop_front(buff, &err);
			if (err == 2)
				printf("Buffer is empty\n");
			else
				printf("%d\n", val);
			break;
		case 4:
			if (circular_buffer_empty(buff))
				printf("Buffer is empty\n");
			else
			{
				circular_buffer_display(buff);
				printf("\n");
			}
			break;
		case 5:
			spr = circular_buffer_empty(buff);
			if (spr == 1)
				printf("1\n");
			else
				printf("0\n");
			break;
		case 6:
			spr = circular_buffer_full(buff);
			if (spr == 1)
				printf("1\n");
			else
				printf("0\n");
			break;
		default:
			printf("Incorrect input data\n");
			break;
		}
	} while (check != 0);
	return 0;
}
