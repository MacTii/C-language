#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 49
#define WORD 20
#define ELEMENTS 10
#define FAILED_TO_ALLOCATE_MEMORY 8
#define COULDNT_OPEN_FILE 4
#define SUCCESS 0

int main()
{
	char *filename = (char *)calloc(N + 1, sizeof(char)); // alokacja
	if (filename == NULL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("Podaj nazwe pliku: ");
	scanf("%49s", filename);

	FILE *f;
	f = fopen(filename, "r"); //plik
	if (f == NULL)
		return free(filename), printf("Couldn't open file"), COULDNT_OPEN_FILE;

	int error;
	struct dictionary_t *d = create_dictionary(ELEMENTS, &error);
	if (error != 0)
		return free(filename), fclose(f), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	char *word = (char *)calloc(WORD, sizeof(char)); // alokacja
	if (word == NULL)
		return free(filename), fclose(f), destroy_dictionary(&d), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	int len = 0;
	while (!feof(f))
	{
		int c = fgetc(f);

		if (isalpha(c))
		{
			*(word + len) = c;
			len++;
		}
		else if (!isalpha(c) && len > 0)
		{
			*(word + len) = '\0';
			len = 0;

			error = dictionary_add_word(d, word);
			if (error != 0)
				return fclose(f), free(word), free(filename), destroy_dictionary(&d), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;
		}
	}

	dictionary_display(d);
	if (d->size == 0)
		printf("Nothing to show");

	free(word);
	free(filename);
	destroy_dictionary(&d);
	fclose(f);

	return SUCCESS;
}