#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define INCORRECT_INPUT 1
#define FAILED_TO_ALLOCATE_MEMORY 8
#define ALLOCATE_MEM_FAIL 2
#define EMPTY_STACK 1
#define SUCCESS 0

int main()
{
	struct stack_t *stack;
	int choice, val, check, err = 0, val_pop;
	check = stack_init(&stack);
	if (check == ALLOCATE_MEM_FAIL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
	do
	{
		printf("Co chcesz zrobic? ");
		check = scanf("%d", &choice);
		if (check != 1)
		{
			stack_destroy(&stack);
			return printf("Incorrect input"), INCORRECT_INPUT;
		}
		switch (choice)
		{
		case 0:
			break;
		case 1:
			printf("Podaj liczbe ");
			check = scanf("%d", &val);
			if (check != 1)
			{
				stack_destroy(&stack);
				return printf("Incorrect input"), INCORRECT_INPUT;
			}
			check = stack_push(stack, val);
			if (check == ALLOCATE_MEM_FAIL)
			{
				stack_destroy(&stack);
				return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
			}
			break;
		case 2:
			val_pop = stack_pop(stack, &err);
			if (err == EMPTY_STACK)
				printf("Stack is empty\n");
			else
				printf("%d\n", val_pop);
			break;
		case 3:
			if (stack_empty(stack) == EMPTY_STACK)
				printf("1\n");
			else
				printf("0\n");
			break;
		case 4:
			stack_display(stack);
			if (stack->head == 0)
				printf("Stack is empty\n");
			break;
		default:
			printf("Incorrect input data\n");
			break;
		}
	} while (choice != 0);
	stack_destroy(&stack);
	return SUCCESS;
}