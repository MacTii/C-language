#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "matrix_utils.h"

#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8
#define UNSUPPORTED_FILE_FORMAT 7
#define COULDNT_CREATE_FILE 5
#define SUCCESS 0
#define SIZE 39

int main()
{
	int w, h;
	printf("Podaj szerokosc i wysokosc: ");
	if (scanf("%d %d", &w, &h) != 2)
		return printf("Incorrect input"), INCORRECT_INPUT;

	if (w < 1 || h < 1)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	struct matrix_t *m = matrix_create_struct(w, h);
	if (m == NULL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("Podaj liczby: ");
	int err = matrix_read(m);
	if (err == 2)
		return printf("Incorrect input"), matrix_destroy_struct(&m), INCORRECT_INPUT;
	else if (err == 1)
		return printf("Failed to allocate memory"), matrix_destroy_struct(&m), FAILED_TO_ALLOCATE_MEMORY;

	while (getchar() != '\n');

	char *filename = (char *)calloc(SIZE + 1, sizeof(char));
	if (filename == NULL)
		return printf("Failed to allocate memory"), matrix_destroy_struct(&m), FAILED_TO_ALLOCATE_MEMORY;

	printf("Podaj sciezke do pliku: ");
	scanf("%39s", filename);

	int len = strlen(filename);
	//printf("%d\n", len);
	//printf("%c %c %c\n", *(filename + len - 1), *(filename + len - 2), *(filename + len - 3));
	if ((*(filename + len - 1) != 't' || *(filename + len - 2) != 'x' || *(filename + len - 3) != 't' || *(filename + len - 4) != '.') &&
		(*(filename + len - 1) != 'n' || *(filename + len - 2) != 'i' || *(filename + len - 3) != 'b' || *(filename + len - 4) != '.'))
		return printf("Unsupported file format"), free(filename), matrix_destroy_struct(&m), UNSUPPORTED_FILE_FORMAT;

	struct matrix_t *temp = matrix_transpose(m);
	if (temp == NULL)
		return printf("Failed to allocate memory"), free(filename), matrix_destroy_struct(&m), FAILED_TO_ALLOCATE_MEMORY;

	if (*(filename + len - 1) == 't' && *(filename + len - 2) == 'x' && *(filename + len - 3) == 't')
	{
		err = matrix_save_t(temp, filename);
		if (err != 0)
			return printf("Couldn't create file"), free(filename), matrix_destroy_struct(&m), matrix_destroy_struct(&temp), COULDNT_CREATE_FILE;
	}

	else
	{
		err = matrix_save_b(temp, filename);
		if (err != 0)
			return printf("Couldn't create file"), free(filename), matrix_destroy_struct(&m), matrix_destroy_struct(&temp), COULDNT_CREATE_FILE;
	}

	printf("File saved");
	matrix_destroy_struct(&m);
	matrix_destroy_struct(&temp);
	free(filename);

	return SUCCESS;
}