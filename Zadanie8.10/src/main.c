#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define INCORRECT_INPUT 1

int longest_series(unsigned int x)
{
	int count = 0, max = 0;

	for (int i = 0; i < 32; i++)
	{
		if (x & 1 << i) // kiedy jest 1
			count++;
		if (count > max)
			max = count;
		if (!(x & 1 << i)) // kiedy jest 0
			count = 0;
	}
	return max;
}

int main()
{
	int number;

	printf("Podaj liczbe: ");

	if (!scanf("%d", &number))
		return printf("Incorrect input"), INCORRECT_INPUT;

	printf("Wynik: %d", longest_series(number));
	return SUCCESS;
}