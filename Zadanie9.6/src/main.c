#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define ALLOCATE_MEM_FAIL 2
#define FAILED_TO_ALLOCATE_MEMORY 8
#define INCORRECT_INPUT 1
#define SUCCESS 0

int main()
{
	struct stack_t *stack;
	int check, val;
	unsigned long long int number;
	check = stack_init(&stack);
	if (check == ALLOCATE_MEM_FAIL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("Enter number: ");
	check = scanf("%llu", &number);
	if (check != 1)
	{
		stack_destroy(&stack);
		return printf("Incorrect input"), INCORRECT_INPUT;
	}

	do
	{
		val = number % 2;
		check = stack_push(stack, val);
		if (check == ALLOCATE_MEM_FAIL)
		{
			stack_destroy(&stack);
			return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
		}
		number /= 2;
	} while (number != 0);

	stack_display(stack);
	stack_destroy(&stack);
	return SUCCESS;
}