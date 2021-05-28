#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define SUCCESS 0
#define FAIL 1
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2

int stats(int *sum, float *avg, int num, ...)
{
	if (!sum || !avg || num < 1)
		return FAIL;

	va_list ap;
	va_start(ap, num);

	*sum = 0;
	*avg = 0;

	for (int i = 0; i < num; i++)
		*sum += va_arg(ap, int);

	*avg = (float)*sum / (float)num;

	va_end(ap);

	return SUCCESS;
}

int main()
{
	int total, tab[2], n, check;
	float average;

	printf("Enter number of elements: ");
	check = scanf("%d", &n);
	if (check != 1)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (n < 1 || n > 3)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	printf("Enter numbers: ");
	for (int i = 0; i < n; i++)
	{
		check = scanf("%d", &tab[i]);
		if (check != 1)
			return printf("Incorrect input"), INCORRECT_INPUT;
	}

	if (n == 1)
		stats(&total, &average, n, tab[0]);
	else if (n == 2)
		stats(&total, &average, n, tab[0], tab[1]);
	else if (n == 3)
		stats(&total, &average, n, tab[0], tab[1], tab[2]);

	printf("%d %f", total, average);
}