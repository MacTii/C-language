#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

#define FAIL 1
#define SUCCESS 0

#define N 999

#define FAILED_TO_ALLOCATE_MEMORY 8
#define SUCCESS 0

int main()
{
	char *txt = (char *)calloc(N + 1, sizeof(char));
	if (txt == NULL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("Enter text: ");
	scanf("%999[^\n]", txt);

	//while (getchar() != '\n');

	int count = 0;
	for (int i = 0; *(txt + i); i++)
	{
		if (isalpha(*(txt + i)))
			count++;
	}

	if (count == 0)
		return free(txt), printf("Nothing to show"), SUCCESS;

	char **res = split_words(txt);
	if (res == NULL)
		return free(txt), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	sort_words(res);

	for (int i = 0; *(res + i); i++)
		printf("%s\n", *(res + i));

	free(txt);
	destroy(res);

	return SUCCESS;
}