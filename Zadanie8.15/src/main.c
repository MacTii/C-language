#include <stdio.h>
#include "functions.h"

DEFINE_ARRAY(int)
CREATE_ARRAY(int)
FREE_ARRAY(int)
SAVE_ARRAY(int)
LOAD_ARRAY(int)
SORT_ARRAY(int)

DEFINE_ARRAY(double)
CREATE_ARRAY(double)
FREE_ARRAY(double)
SAVE_ARRAY(double)
LOAD_ARRAY(double)
SORT_ARRAY(double)

//filename
#define FILE_NAME 30

//error codes main
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define COULDNT_OPEN_FILE 4
#define COULDNT_CREATE_FILE 5
#define FILE_CORRUPTED 6
#define FAILED_TO_ALLOCATE_MEMORY 8

//error codes .h
#define SUCCESS 0
#define FAIL 1
#define FILE_FAIL 2
#define INCORRECT_FAIL 3
#define ALLOCATE_FAIL 4

int main()
{
	char *name = (char *)malloc(sizeof(char) * FILE_NAME);
	if (!name)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("Enter filename: ");
	scanf("%30s", name);

	int type;
	printf("Choose your type: ");
	int x = scanf("%d", &type);
	if (!x)
		return printf("Incorrect input"), free(name), INCORRECT_INPUT;
	if (type < 0 || type > 1)
		return printf("Incorrect input data"), free(name), INCORRECT_INPUT_DATA;

	struct array_int_t *array_int;
	struct array_double_t *array_double;
	int error = 0;

	switch (type)
	{
	case 0:
		error = load_array_int(&array_int, name);

		if (error == FILE_FAIL)
			return printf("Couldn't open file"), free(name), COULDNT_OPEN_FILE;
		else if (error == INCORRECT_FAIL)
			return printf("File corrupted"), free(name), FILE_CORRUPTED;
		else if (error == ALLOCATE_FAIL)
			return printf("Failed to allocate memory"), free(name), FAILED_TO_ALLOCATE_MEMORY;

		sort_array_int(array_int);

		error = save_array_int(array_int, name);

		if (error == FILE_FAIL)
			return printf("Couldn't create file"), free(name), free_array_int(array_int), COULDNT_CREATE_FILE;
		else
			return printf("File saved"), free(name), free_array_int(array_int), SUCCESS;
		break;

	case 1:
		error = load_array_double(&array_double, name);

		if (error == FILE_FAIL)
			return printf("Couldn't open file"), free(name), COULDNT_OPEN_FILE;
		else if (error == INCORRECT_FAIL)
			return printf("File corrupted"), free(name), FILE_CORRUPTED;
		else if (error == ALLOCATE_FAIL)
			return printf("Failed to allocate memory"), free(name), FAILED_TO_ALLOCATE_MEMORY;

		sort_array_double(array_double);

		error = save_array_double(array_double, name);

		if (error == FILE_FAIL)
			return printf("Couldn't create file"), free(name), free_array_double(array_double), COULDNT_CREATE_FILE;
		else
			return printf("File saved"), free(name), free_array_double(array_double), SUCCESS;
		break;
	}

	return SUCCESS;
}
