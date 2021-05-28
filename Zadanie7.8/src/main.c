#include <stdio.h>
#include <stdlib.h>
#include "function.h"

#define SUCCESS 0

int main()
{
	printf("%llu\n", bits_to_number(NULL, 3, 1, 1, 1));
	printf("%llu\n", bits_to_number(NULL, 8, 1, 0, 0, 0, 0, 0, 0, 1));
	printf("%llu", bits_to_number(NULL, 32, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0));

	return SUCCESS;
}