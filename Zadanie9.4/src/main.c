#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define SUCCESS 0
#define COULDNT_CREATE_FILE 5
#define FAILED_TO_ALLOCATE_MEMORY 8
#define NOT_ENOUGH_ARGUMENTS 9

#define ALLOCATE_FAIL 3
#define ERR_FILE 2
#define INCORRECT 1

int main(int argc, char **argv)
{
	if (argc < 2)
		return printf("Not enough arguments\n"), NOT_ENOUGH_ARGUMENTS;
	struct stack_t *stack;
	int error = 0;
	for (int i = 1; i < argc; i++)
	{
		error = stack_load(&stack, *(argv + i));
		if (error == ERR_FILE || error == INCORRECT)
		{
			printf("Couldn't open file %s\n", *(argv + i));
			continue;
		}
		else if (error == ALLOCATE_FAIL)
			return printf("Failed to allocate memory\n"), FAILED_TO_ALLOCATE_MEMORY;

		error = stack_save(stack, *(argv + i));
		if (error == INCORRECT || error == ERR_FILE)
		{
			printf("Couldn't create file\n");
			stack_destroy(&stack);
			return COULDNT_CREATE_FILE;
		}
		else
			printf("File %s saved\n", *(argv + i));
		stack_destroy(&stack);
	}
	return SUCCESS;
}