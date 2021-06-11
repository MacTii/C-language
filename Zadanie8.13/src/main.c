#include <stdio.h>
#include "functions.h"
#include <stdint.h>

#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define SUCCESS 0

int main()
{
	int type, set = 0, cleared = 0;

	printf("Enter data type: ");
	if (!scanf("%d", &type))
		return printf("Incorrect input"), INCORRECT_INPUT;

	if (type < 0 || type > 2)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	printf("Enter an integer number: ");
	unsigned int int_type;
	unsigned short short_type;
	unsigned long long_type;

	if (type == 0)
	{
		if (!scanf("%u", &int_type))
			return printf("Incorrect input"), INCORRECT_INPUT;

		COUNT_BITS(int_type, &set, &cleared);
		printf("%d\n%d\n", set, cleared);

		DISPLAY_BITS(int_type);
		printf("\n");

		REVERSE_BITS(&int_type);
		DISPLAY_BITS(int_type);
	}
	if (type == 1)
	{
		if (!scanf("%hu", &short_type))
			return printf("Incorrect input"), INCORRECT_INPUT;

		COUNT_BITS(short_type, &set, &cleared);
		printf("%d\n%d\n", set, cleared);

		DISPLAY_BITS(short_type);
		printf("\n");

		REVERSE_BITS(&short_type);
		DISPLAY_BITS(short_type);
	}
	if (type == 2)
	{
		if (!scanf("%lu", &long_type))
			return printf("Incorrect input"), INCORRECT_INPUT;

		COUNT_BITS(long_type, &set, &cleared);
		printf("%d\n%d\n", set, cleared);

		DISPLAY_BITS(long_type);
		printf("\n");

		REVERSE_BITS(&long_type);
		DISPLAY_BITS(long_type);
	}
	return SUCCESS;
}