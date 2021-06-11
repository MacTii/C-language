#include <stdio.h>
#include <stdint.h>

#define SUCCESS 0
#define INCORRECT_INPUT 1

int64_t negation(int64_t value)
{
	return ~value + (int64_t)1;
}

int main()
{
	int64_t number;
	printf("Podaj liczbe: ");

	if (!scanf("%ld", &number))
		return printf("Input error"), negation(INCORRECT_INPUT);

	printf("Wynik: %ld", negation(number));
	return SUCCESS;
}