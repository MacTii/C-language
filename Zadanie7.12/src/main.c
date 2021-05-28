#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NOT_ENOUGH_ARGUMENTS 9
#define INCORRECT_INPUT 1
#define SUCCESS 0
#define FAIL 1

int check_number(char *number)
{
	if (!number)
		return FAIL;

	int minus = 0;
	if (*number == '-')
		minus = 1;

	int len = strlen(number);
	for (int i = minus; i < len; i++)
		if (!isdigit(*(number + i)))
			return FAIL;

	return SUCCESS;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return printf("Not enough arguments"), NOT_ENOUGH_ARGUMENTS;

	int sum = 0;
	for (int i = 1; i < argc; i++)
	{
		if (check_number(*(argv + i)) == FAIL)
			return printf("Incorrect input"), INCORRECT_INPUT;

		int num = atoi(*(argv + i));
		sum += num;
	}

	printf("%d", sum);

	return SUCCESS;
}