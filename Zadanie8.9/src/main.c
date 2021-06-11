#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define SUCCESS 0
#define INCORRECT_INPUT 1

	int
	is_sparse(uint64_t value)
{
	int count = 0, check = 1;

	for (int i = 0; i < 64; i++)
	{
		if (value & (uint64_t)1 << i) // kiedy jest 1
			count++;
		if (count == 2)
			check = 0;
		if (!(value & (uint64_t)1 << i)) // kiedy jest 0
			count = 0;
	}
	return check;
}

void hexdecimal(uint64_t value, char *res)
{
	for (int i = 15; i >= 0; i--)
	{
		if (value % (uint64_t)16 < 10)
			res[i] = (value % 16) + '0';
		else
		{
			if (value % (uint64_t)16 == 10)
				res[i] = 'a';
			if (value % (uint64_t)16 == 11)
				res[i] = 'b';
			if (value % (uint64_t)16 == 12)
				res[i] = 'c';
			if (value % (uint64_t)16 == 13)
				res[i] = 'd';
			if (value % (uint64_t)16 == 14)
				res[i] = 'e';
			if (value % (uint64_t)16 == 15)
				res[i] = 'f';
		}
		value /= (uint64_t)16;
	}
	res[16] = '\0';
}

int main()
{
	uint64_t number;
	char res[17];
	printf("Podaj liczbe: ");

	if (!scanf("%lu", &number))
		return printf("Incorrect input"), INCORRECT_INPUT;

	hexdecimal(number, res);
	printf("Liczba: %s, ", res);
	printf("Wynik: %d", is_sparse(number));
	return SUCCESS;
}