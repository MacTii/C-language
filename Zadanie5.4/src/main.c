#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//validate errors
#define FAIL_VALIDATE -1
#define SUCCESS_VALIDATE 0
#define INCORRECT_NUMBER_VALIDATE 2

//compare errors
#define EQUAL 0
#define NUMBER1_HIGHER 1
#define NUMBER2_HIGHER -1
#define FAIL_COMPARE 2
#define INCORRECT_NUMBER_COMPARE 3

//add errrors
#define SUCCESS_ADD 0
#define FAIL_ADD 1
#define INCORRECT_NUMBER_ADD 2
#define FAIL_TO_ALLOCATE_MEMORY_ADD 3

//subtract errors;
#define SUCCESS_SUBTRACT 0
#define FAIL_SUBTRACT 1
#define INCORRECT_NUMBER_SUBTRACT 2
#define FAIL_TO_ALLOCATE_MEMORY_SUBTRACT 3

//main errors
#define SUCCESS 0
#define FAILED_TO_ALLOCATE_MEMORY 8
#define INCORRECT_INPUT 1
#define N 200

int subtract(const char *number1, const char *number2, char **result);
int add(const char *number1, const char *number2, char **result);

int validate(const char *number)
{
	if (!number)
		return FAIL_VALIDATE;

	bool is_negative = 0;
	int len = strlen(number);

	if (len < 1)
		return INCORRECT_NUMBER_VALIDATE;

	if (*number == '-')
		is_negative = 1;

	if (is_negative && len < 2)
		return INCORRECT_NUMBER_VALIDATE;

	if (*number == '0' && len > 1)
		return INCORRECT_NUMBER_VALIDATE;

	for (int i = is_negative ? 1 : 0; i < len; i++)
		if (*(number + i) < '0' || *(number + i) > '9')
			return INCORRECT_NUMBER_VALIDATE;

	return SUCCESS_VALIDATE;
}

int compare(const char *number1, const char *number2)
{
	if (!number1 || !number2)
		return FAIL_COMPARE;

	int error = validate(number1);
	if (error == INCORRECT_NUMBER_VALIDATE)
		return INCORRECT_NUMBER_COMPARE;

	error = validate(number2);
	if (error == INCORRECT_NUMBER_VALIDATE)
		return INCORRECT_NUMBER_COMPARE;

	int len1 = strlen(number1);
	int len2 = strlen(number2);

	bool is_negative_number1 = 0, is_negative_number2 = 0;
	if (*number1 == '-')
		is_negative_number1 = 1;
	if (*number2 == '-')
		is_negative_number2 = 1;

	if (is_negative_number1 && !is_negative_number2)
		return NUMBER2_HIGHER;

	else if (!is_negative_number1 && is_negative_number2)
		return NUMBER1_HIGHER;

	if (is_negative_number1 && is_negative_number2)
	{
		if (len1 > len2)
			return NUMBER2_HIGHER;
		if (len1 < len2)
			return NUMBER1_HIGHER;
		if (len1 == len2)
		{
			for (int i = 1; i < len1; i++)
			{
				if (*(number1 + i) > *(number2 + i))
					return NUMBER2_HIGHER;
				if (*(number1 + i) < *(number2 + i))
					return NUMBER1_HIGHER;
			}
		}
	}

	if (!is_negative_number1 && !is_negative_number2)
	{
		if (len1 > len2)
			return NUMBER1_HIGHER;
		if (len1 < len2)
			return NUMBER2_HIGHER;
		if (len1 == len2)
		{
			for (int i = 0; i < len1; i++)
			{
				if (*(number1 + i) > *(number2 + i))
					return NUMBER1_HIGHER;
				if (*(number1 + i) < *(number2 + i))
					return NUMBER2_HIGHER;
			}
		}
	}

	return EQUAL;
}

int add_negative(const char *number1, const char *number2, char **result)
{
	int len1 = strlen(number1);
	int len2 = strlen(number2);

	int size = 0;
	if (len1 > len2)
		size = len1;

	else
		size = len2;

	int i, p = 0, w, ctrl, koniec = 0;
	char *poczatek = *result;
	for (i = 0; i < size; i++)
	{
		ctrl = 1;
		if (i < len1 && i < len2)
		{
			w = (*(number1 + len1 - 1 - i) - '0') + (*(number2 + len2 - 1 - i) - '0') + p;
			p = w / 10;
			*(*result + i) = ((w % 10) + '0');
			ctrl = 0;
			koniec++;
		}
		if (p == 1 && len1 == len2 && i == size - 1)
		{
			*(*result + i + 1) = p + '0';
			koniec++;
		}
		if (len1 > len2 && ctrl == 1)
		{
			w = (*(number1 + len1 - 1 - i) - '0') + p;
			p = w / 10;
			*(*result + i) = ((w % 10) + '0');
			koniec++;
		}
		if (len1 < len2 && ctrl == 1)
		{
			w = (*(number2 + len2 - 1 - i) - '0') + p;
			p = w / 10;
			*(*result + i) = ((w % 10) + '0');
			koniec++;
		}
		if (p == 1 && len1 != len2 && i == size - 1)
		{
			char *re_result = (char *)realloc(*result, size + 3);
			if (!re_result)
				return free(result), FAIL_TO_ALLOCATE_MEMORY_SUBTRACT;

			*(re_result + i + 1) = p + '0';
			koniec++;

			*(re_result + koniec) = '-';
			*(re_result + koniec + 1) = '\0';

			char *end = re_result + koniec;
			char *begin = re_result;

			while (begin < end)
			{
				char tmp = *begin;
				*begin = *end;
				*end = tmp;
				begin++;
				end--;
			}

			*result = re_result;
			return SUCCESS_ADD;
		}
	}

	*(*result + koniec) = '-';

	char *end = poczatek + koniec;
	char *begin = poczatek;

	while (begin < end)
	{
		char tmp = *begin;
		*begin = *end;
		*end = tmp;
		begin++;
		end--;
	}

	*(*result + koniec + 1) = '\0';

	return SUCCESS_ADD;
}

int subtract_higher_negative(const char *number2, const char *number1, char **result)
{
	if (!number1 || !number2 || !result)
		return FAIL_SUBTRACT;

	int len1 = strlen(number1);
	int len2 = strlen(number2);

	int size = 0;
	if (len1 > len2)
		size = len1;

	else
		size = len2;

	int i, w, ctrl, koniec = 0, tmp = 0;
	char *poczatek = *result;
	for (i = 0; i < size; i++)
	{
		ctrl = 1;
		if (i < len1 && i < len2)
		{
			w = (*(number1 + len1 - 1 - i) - '0') - (*(number2 + len2 - 1 - i) - '0') - tmp;
			if (w < 0)
			{
				*(*result + i) = w + 10 + '0';
				tmp = 1;
			}
			else
			{
				*(*result + i) = w + '0';
				tmp = 0;
			}
			ctrl = 0;
			koniec++;
		}
		if (len1 > len2 && ctrl == 1)
		{
			w = (*(number1 + len1 - 1 - i) - '0') - tmp;
			if (w < 0)
			{
				*(*result + i) = (w + 10) + '0';
				tmp = 1;
			}
			else
			{
				*(*result + i) = w + '0';
				tmp = 0;
			}
			/*if (*(*result + i) < '0' || *(*result + i) > '9')
                k = 1;*/
			koniec++;
		}
		if (len1 < len2 && ctrl == 1)
		{
			w = (*(number2 + len1 - 1 - i) - '0') - tmp;
			if (w < 0)
			{
				*(*result + i) = (w + 10) + '0';
				tmp = 1;
			}
			else
			{
				*(*result + i) = w + '0';
				tmp = 0;
			}
			/*if (*(*result + i) < '0' || *(*result + i) > '9')
                k = 1;*/
			koniec++;
		}
	}

	int size_pom = 0, size_allocate = 0;
	bool check = 0;
	for (int i = 0; i < koniec; i++)
	{
		if (*(*result + i) != '0')
		{
			check = 1;
			size_pom = 0;
		}
		else
			size_pom++;
		size_allocate++;
	}

	if (check && size_pom > 0)
	{
		char *re_result = (char *)realloc(*result, sizeof(char) * (size_allocate + 2 - size_pom));
		if (!re_result)
			return free(result), FAIL_TO_ALLOCATE_MEMORY_SUBTRACT;

		for (int i = 0; i < koniec - size_pom; i++)
			*(re_result + i) = *(*result + i);

		*(re_result + koniec - size_pom) = '-';
		*(re_result + koniec - size_pom + 1) = '\0';

		char *end = re_result + koniec - size_pom;
		char *begin = re_result;

		while (begin < end)
		{
			char tmp = *begin;
			*begin = *end;
			*end = tmp;
			begin++;
			end--;
		}

		*result = re_result;

		return SUCCESS_SUBTRACT;
	}
	if (!check)
	{
		char *re_result = (char *)realloc(*result, sizeof(char) * 2);
		if (!re_result)
			return free(result), FAIL_TO_ALLOCATE_MEMORY_SUBTRACT;

		*re_result = '0';
		*(re_result + 1) = '\0';
		*result = re_result;
		return SUCCESS_SUBTRACT;
	}

	*(*result + koniec) = '-';

	char *end = poczatek + koniec;
	char *begin = poczatek;

	while (begin < end)
	{
		char tmp = *begin;
		*begin = *end;
		*end = tmp;
		begin++;
		end--;
	}

	*(*result + koniec + 1) = '\0';

	return SUCCESS_SUBTRACT;
}

int subtract_higher(const char *number1, const char *number2, char **result)
{
	if (!number1 || !number2 || !result)
		return FAIL_SUBTRACT;

	int len1 = strlen(number1);
	int len2 = strlen(number2);

	int size = 0;
	if (len1 > len2)
		size = len1;

	else
		size = len2;

	int i, ctrl, w = 0, koniec = 0, tmp = 0, k = 0;
	char *poczatek = *result;
	for (i = 0; i < size; i++)
	{
		ctrl = 1;
		if (i < len1 && i < len2)
		{
			w = (*(number1 + len1 - 1 - i) - '0') - (*(number2 + len2 - 1 - i) - '0') - tmp;
			if (w == 0 && i == size - 1)
				break;
			if (w < 0)
			{
				*(*result + i) = (w + 10) + '0';
				tmp = 1;
			}
			else
			{
				*(*result + i) = w + '0';
				tmp = 0;
			}
			koniec++;
			ctrl = 0;
		}
		if (len1 > len2 && ctrl == 1)
		{
			w = (*(number1 + len1 - 1 - i) - '0') - tmp;
			if (w < 0)
			{
				*(*result + i) = (w + 10) + '0';
				tmp = 1;
			}
			else
			{
				*(*result + i) = w + '0';
				tmp = 0;
			}
			if (*(*result + i) < '0' || *(*result + i) > '9')
				k = 1;
			koniec++;
		}
		if (len1 < len2 && ctrl == 1)
		{
			w = (*(number2 + len1 - 1 - i) - '0') - tmp;
			if (w < 0)
			{
				*(*result + i) = (w + 10) + '0';
				tmp = 1;
			}
			else
			{
				*(*result + i) = w + '0';
				tmp = 0;
			}
			if (*(*result + i) < '0' || *(*result + i) > '9')
				k = 1;
			koniec++;
		}
	}

	int size_pom = 0, size_allocate = 0;
	bool check = 0;
	koniec -= k;
	for (int i = 0; i < koniec; i++)
	{
		if (*(*result + i) != '0')
		{
			check = 1;
			size_pom = 0;
		}
		else
			size_pom++;
		size_allocate++;
	}

	if (check && size_pom > 0)
	{
		char *re_result = (char *)realloc(*result, sizeof(char) * (size_allocate + 1 - size_pom));
		if (!re_result)
			return free(result), FAIL_TO_ALLOCATE_MEMORY_SUBTRACT;

		for (int i = 0; i < koniec - size_pom; i++)
			*(re_result + i) = *(*result + i);

		*(re_result + koniec - size_pom) = '\0';

		char *end = re_result + koniec - size_pom - 1;
		char *begin = re_result;

		while (begin < end)
		{
			char tmp = *begin;
			*begin = *end;
			*end = tmp;
			begin++;
			end--;
		}

		*result = re_result;

		return SUCCESS_SUBTRACT;
	}
	if (!check)
	{
		char *re_result = (char *)realloc(*result, sizeof(char) * 2);
		if (!re_result)
			return free(result), FAIL_TO_ALLOCATE_MEMORY_SUBTRACT;

		*re_result = '0';
		*(re_result + 1) = '\0';
		*result = re_result;
		return SUCCESS_SUBTRACT;
	}
	if (k)
	{
		char *re_result = (char *)realloc(*result, sizeof(char) * (size_allocate + 1));
		if (!re_result)
			return free(result), FAIL_TO_ALLOCATE_MEMORY_SUBTRACT;
	}

	char *end = poczatek + koniec - 1;
	char *begin = poczatek;

	while (begin < end)
	{
		char tmp = *begin;
		*begin = *end;
		*end = tmp;
		begin++;
		end--;
	}

	*(*result + koniec) = '\0';

	return SUCCESS_SUBTRACT;
}

int add_plus_minus(const char *number1, const char *number2, char **result)
{
	if (!number1 || !number2 || !result)
		return FAIL_ADD;

	int len1 = strlen(number1); //3
	int len2 = strlen(number2); //4

	int size = 0;
	if (len1 > len2)
		size = len1;

	else
		size = len2; //4

	int i, p = 0, w, ctrl, koniec = 0;
	char *poczatek = *result;
	for (i = 0; i < size; i++)
	{
		ctrl = 1;
		if (i < len1 && i < len2)
		{
			w = (*(number1 + len1 - 1 - i) - '0') + (*(number2 + len2 - 1 - i) - '0') + p;
			p = w / 10;
			*(*result + i) = ((w % 10) + '0');
			ctrl = 0;
			koniec++;
		}
		if (p == 1 && len1 == len2 && i == size - 1)
		{
			*(*result + i + 1) = p + '0';
			koniec++;
		}
		if (len1 > len2 && ctrl == 1)
		{
			w = (*(number1 + len1 - 1 - i) - '0') + p;
			p = w / 10;
			*(*result + i) = ((w % 10) + '0');
			koniec++;
		}
		if (len1 < len2 && ctrl == 1)
		{
			w = (*(number2 + len2 - 1 - i) - '0') + p;
			p = w / 10;
			*(*result + i) = ((w % 10) + '0');
			koniec++;
		}
		if (p == 1 && len1 != len2 && i == size - 1)
		{
			*(*result + i + 1) = p + '0';
			koniec++;
		}
	}

	char *end = poczatek + koniec - 1;
	char *begin = poczatek;

	while (begin < end)
	{
		char tmp = *begin;
		*begin = *end;
		*end = tmp;
		begin++;
		end--;
	}

	*(*result + koniec) = '\0';

	return SUCCESS_ADD;
}

int subtract(const char *number1, const char *number2, char **result)
{
	if (!number1 || !number2 || !result)
		return FAIL_SUBTRACT;

	int error = validate(number1);
	if (!!error)
		return INCORRECT_NUMBER_ADD;

	error = validate(number2);
	if (!!error)
		return INCORRECT_NUMBER_ADD;

	int len1 = strlen(number1);
	int len2 = strlen(number2);

	int size = 0;
	if (len1 > len2)
		size = len1;

	else
		size = len2;

	*result = (char *)calloc(size + 2, sizeof(char));
	if (!*result)
		return FAIL_TO_ALLOCATE_MEMORY_SUBTRACT;

	if (*number1 == '-') //-
	{
		if (*number2 == '-') // -x-(-y) --> -x+y --> y-x
		{
			for (int i = 0; i < len1; i++)
			{
				if (*(number1 + i + 1) - '0' > *(number2 + i + 1) - '0')
					return subtract_higher_negative(number2 + 1, number1 + 1, result);
				if (*(number1 + i + 1) - '0' < *(number2 + i + 1) - '0')
					return subtract_higher(number2 + 1, number1 + 1, result);
			}
			return subtract_higher(number1 + 1, number2 + 1, result);
		}
		else // -x-y --> -x+(-y) --> -1(x+y)
			return add_negative(number1 + 1, number2, result);
	}
	else //+
	{
		if (*number2 == '-') // x-(-y) --> x+y
			return add_plus_minus(number1, number2 + 1, result);
		else // x-y
		{
			if (len1 == len2)
			{
				for (int i = 0; i < len1; i++)
				{
					if (*(number1 + i) - '0' > *(number2 + i) - '0')
						return subtract_higher(number1, number2, result);
					if (*(number1 + i) - '0' < *(number2 + i) - '0')
						return subtract_higher_negative(number1, number2, result);
				}
				return subtract_higher_negative(number1, number2, result);
			}
			else if (len1 > len2)
				return subtract_higher(number1, number2, result);
			else
				return subtract_higher_negative(number1, number2, result);
		}
	}

	return SUCCESS_SUBTRACT;
}

int subtract_minus_plus(const char *number1, const char *number2, char **result)
{
	if (!number1 || !number2 || !result)
		return FAIL_SUBTRACT;

	int len1 = strlen(number1);
	int len2 = strlen(number2);

	if (len1 == len2)
	{
		for (int i = 0; i < len1; i++)
		{
			if (*(number1 + i) - '0' > *(number2 + i) - '0')
				return subtract_higher(number1, number2, result);
			if (*(number1 + i) - '0' < *(number2 + i) - '0')
				return subtract_higher_negative(number1, number2, result);
		}

		return subtract_higher_negative(number1, number2, result);
	}
	else if (len1 > len2)
		return subtract_higher(number1, number2, result);
	else
		return subtract_higher_negative(number1, number2, result);

	return SUCCESS_SUBTRACT;
}

int subtract_plus_minus(const char *number1, const char *number2, char **result)
{
	if (!number1 || !number2 || !result)
		return FAIL_SUBTRACT;

	int len1 = strlen(number1);
	int len2 = strlen(number2);

	if (len1 == len2)
	{
		for (int i = 0; i < len1; i++)
		{
			if (*(number1 + i) - '0' > *(number2 + i) - '0')
				return subtract_higher(number1, number2, result);
			if (*(number1 + i) - '0' < *(number2 + i) - '0')
				return subtract_higher_negative(number1, number2, result);
		}

		return subtract_higher_negative(number1, number2, result);
	}
	else if (len1 > len2)
		return subtract_higher(number1, number2, result);
	else
		return subtract_higher_negative(number1, number2, result);

	return SUCCESS_SUBTRACT;
}

int add(const char *number1, const char *number2, char **result)
{
	if (!number1 || !number2 || !result)
		return FAIL_ADD;

	int error = validate(number1);
	if (!!error)
		return INCORRECT_NUMBER_ADD;

	error = validate(number2);
	if (!!error)
		return INCORRECT_NUMBER_ADD;

	int len1 = strlen(number1); //3
	int len2 = strlen(number2); //4

	int size = 0;
	if (len1 > len2)
		size = len1;

	else
		size = len2; //4

	*result = (char *)calloc(size + 2, sizeof(char));
	if (!*result)
		return FAIL_TO_ALLOCATE_MEMORY_ADD;

	if (*number1 == '-')
	{
		if (*number2 == '-') // -x+(-y) --> -1*(x+y)
			return add_negative(number1 + 1, number2 + 1, result);
		else // -x+y --> y-x
			return subtract_minus_plus(number2, number1 + 1, result);
	}

	else //+
	{
		if (*number2 == '-') // x+(-y) --> x-y
			return subtract_plus_minus(number1, number2 + 1, result);
		else // x+y
		{
			int i, p = 0, w, ctrl, koniec = 0;
			char *poczatek = *result;
			for (i = 0; i < size; i++)
			{
				ctrl = 1;
				if (i < len1 && i < len2)
				{
					w = (*(number1 + len1 - 1 - i) - '0') + (*(number2 + len2 - 1 - i) - '0') + p;
					p = w / 10;
					*(*result + i) = ((w % 10) + '0');
					ctrl = 0;
					koniec++;
				}
				if (p == 1 && len1 == len2 && i == size - 1)
				{
					*(*result + i + 1) = p + '0';
					koniec++;
				}
				if (len1 > len2 && ctrl == 1)
				{
					w = (*(number1 + len1 - 1 - i) - '0') + p;
					p = w / 10;
					*(*result + i) = ((w % 10) + '0');
					koniec++;
				}
				if (len1 < len2 && ctrl == 1)
				{
					w = (*(number2 + len2 - 1 - i) - '0') + p;
					p = w / 10;
					*(*result + i) = ((w % 10) + '0');
					koniec++;
				}
				if (p == 1 && len1 != len2 && i == size - 1)
				{
					*(*result + i + 1) = p + '0';
					koniec++;
				}
			}

			char *end = poczatek + koniec - 1;
			char *begin = poczatek;

			while (begin < end)
			{
				char tmp = *begin;
				*begin = *end;
				*end = tmp;
				begin++;
				end--;
			}

			*(*result + koniec) = '\0';
		}
	}

	return SUCCESS_ADD;
}

int main()
{
	char *res;
	int error;

	char *number1 = (char *)malloc(sizeof(char) * (N + 1));
	if (!number1)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	char *number2 = (char *)malloc(sizeof(char) * (N + 1));
	if (!number2)
		return free(number1), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("Podaj pierwsza liczbe: ");
	scanf("%200s", number1);

	while (getchar() != '\n');

	printf("Podaj druga liczbe: ");
	scanf("%200s", number2);

	while (getchar() != '\n');

	if (!!validate(number1) || !!validate(number2))
		return free(number1), free(number2), printf("Incorrect input"), INCORRECT_INPUT;

	error = add(number1, number2, &res);

	if (error == 3)
		return free(number1), free(number2), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("%s\n", res);
	free(res);

	error = subtract(number1, number2, &res);

	if (error == 3)
		return free(number1), free(number2), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	printf("%s", res);

	free(res);
	free(number1);
	free(number2);

	return 0;
}
