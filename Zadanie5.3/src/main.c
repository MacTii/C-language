#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define INCORRECT_INPUT 1
#define FAILED_TO_ALLOCATE_MEMORY 8

#define INCORRECT 1
#define CORRECT_NAME 2
#define CORRECT_NAME_SURNAME 3
#define CORRECT_ALL 0

#define N 99
#define FILE_SIZE 39

#define SUCCESS 0
#define FAIL 1
#define FILE_FAIL 2
#define FILE_CORRUPTED 3
#define FAIL_ALLOCATED_MEMORY 4

struct student_t
{
	char *name;
	char *surname;
	int index;
};

void destroy(struct student_t **s)
{
	if (s == NULL || *s == NULL)
		return;
	if ((*s)->name)
		free((*s)->name);
	if ((*s)->surname)
		free((*s)->surname);
	free(*s);
}

struct student_t *read(int *err_code)
{
	char *text = (char *)calloc(N + 1, sizeof(char));
	if (text == NULL)
	{
		if (err_code)
			*err_code = FAIL_ALLOCATED_MEMORY;
		return NULL;
	}
	struct student_t *p = (struct student_t *)calloc(1, sizeof(struct student_t));
	if (p == NULL)
	{
		if (err_code)
			*err_code = FAIL_ALLOCATED_MEMORY;
		return free(text), NULL;
	}
	printf("Podaj dane: ");
	int przecinek1 = 1;
	int koniec1 = 0;
	int i, size = 0, begin;
	bool check = 1;
	bool przecinek = 1;
	for (i = 0; i < N; i++)
	{
		scanf("%c", text + i);
		if (isalpha(*(text + i)))
		{
			if (check)
			{
				begin = i;
				check = 0;
			}
			size++;
		}
		if (*(text + i) == ',')
		{
			przecinek = 0;
			koniec1 = 1;
			p->name = (char *)calloc(size + 1, sizeof(char));
			if (p->name == NULL)
			{
				if (err_code)
					*err_code = FAIL_ALLOCATED_MEMORY;
				return free(text), destroy(&p), NULL;
			}
			for (int j = 0, z = begin; j < size; j++, z++)
				*(p->name + j) = *(text + z);
			*(p->name + size) = '\0';
			break;
		}
		if (*(text + i) == '\n')
		{
			przecinek1 = 0;
			if (err_code != NULL)
				*err_code = INCORRECT;
			return free(text), destroy(&p), NULL;
		}
	}
	if (koniec1 == 0)
	{
		if (err_code != NULL)
			*err_code = INCORRECT;
		return free(text), destroy(&p), NULL;
	}
	i++;
	scanf("%c", text + i);
	if (*(text + i) != ' ')
	{
		if (err_code != NULL)
			*err_code = INCORRECT;
		return free(text), destroy(&p), NULL;
	}
	int przecinek2 = 1;
	int koniec2 = 0;
	int j;
	check = 1;
	size = 0;
	bool check2 = 0, check3 = 1, check4 = 0, check5 = 1, check6 = 0;
	for (j = i + 1; j < N; j++)
	{
		scanf("%c", text + j);
		if (isalpha(*(text + j)))
			check2 = 1;
		if (*(text + j) == ' ' && check4)
		{
			size--;
			check3 = 0;
			check4 = 0;
			check5 = 0;
			check6 = 0;
		}
		if (isalpha(*(text + j)))
			check6 = 0;
		if (*(text + j) == ',' && check6)
			size--;
		if (*(text + j) == ' ' && check5)
		{
			check4 = 1;
			check6 = 1;
		}
		if (check2 && *(text + j) != ',' && check3)
		{
			if (check)
			{
				begin = j;
				check = 0;
			}
			size++;
		}
		if (*(text + j) == ',')
		{
			przecinek = 0;
			koniec2 = 1;
			p->surname = (char *)calloc(size + 1, sizeof(char));
			if (p->surname == NULL)
			{
				if (err_code)
					*err_code = FAIL_ALLOCATED_MEMORY;
				return free(text), destroy(&p), NULL;
			}
			for (int k = 0, z = begin; k < size; k++, z++)
				*(p->surname + k) = *(text + z);
			*(p->surname + size) = '\0';
			break;
		}
		if (*(text + j) == '\n')
		{
			przecinek2 = 0;
			if (przecinek1 == 0 && przecinek2 == 0)
			{
				if (err_code != NULL)
					*err_code = INCORRECT;
				return free(text), destroy(&p), NULL;
			}
			if (err_code != NULL)
				*err_code = CORRECT_NAME;
			return free(text), destroy(&p), NULL;
		}
	}
	if (koniec2 == 0)
	{
		if (err_code != NULL)
			*err_code = CORRECT_NAME;
		return free(text), destroy(&p), NULL;
	}
	j++;
	scanf("%c", text + j);
	if (*(text + j) != ' ')
	{
		if (err_code != NULL)
			*err_code = INCORRECT;
		return free(text), destroy(&p), NULL;
	}
	int save_tmp = 0, wykladnik = 1;
	for (int l = j + 1; l < N; l++)
	{
		scanf("%c", text + l);
		if (*(text + l) == '\n' || *(text + l) == ',')
		{
			p->index = save_tmp;
			break;
		}
		int tmp = *(text + l) - '0';
		if (!isdigit(*(text + l)))
		{
			if (err_code != NULL)
				*err_code = CORRECT_NAME_SURNAME;
			return free(text), destroy(&p), NULL;
		}
		else
		{
			save_tmp = save_tmp * wykladnik + tmp;
			wykladnik = 10;
		}
	}
	if (przecinek)
	{
		if (err_code)
			*err_code = CORRECT_NAME_SURNAME;
		return free(text), destroy(&p), NULL;
	}
	if (err_code != NULL)
		*err_code = CORRECT_ALL;
	free(text);
	return p;
}

int save_student_b(const struct student_t *s, const char *filename)
{
	if (s == NULL || filename == NULL)
		return FAIL;

	FILE *f = fopen(filename, "wb");
	if (f == NULL)
		return FILE_FAIL;

	int name_len = strlen(s->name);
	int surname_len = strlen(s->surname);

	fwrite(&name_len, sizeof(int), 1, f);
	fwrite(s->name, sizeof(char), name_len, f);

	fwrite(&surname_len, sizeof(int), 1, f);
	fwrite(s->surname, sizeof(char), surname_len, f);

	fwrite(&s->index, sizeof(int), 1, f);

	fclose(f);

	return SUCCESS;
}

struct student_t *load_student_b(const char *filename, int *err_code)
{
	if (filename == NULL)
	{
		if (err_code)
			*err_code = FAIL;
		return NULL;
	}

	FILE *f = fopen(filename, "rb+");
	if (f == NULL)
	{
		if (err_code)
			*err_code = FILE_FAIL;
		return NULL;
	}

	int check;
	unsigned int name_len, surname_len;

	struct student_t *p = (struct student_t *)calloc(1, sizeof(struct student_t));
	if (p == NULL)
	{
		if (err_code)
			*err_code = FAIL_ALLOCATED_MEMORY;
		return fclose(f), NULL;
	}

	check = fread(&name_len, sizeof(unsigned int), 1, f);
	if (!check || feof(f))
	{
		if (err_code)
			*err_code = FILE_CORRUPTED;
		return destroy(&p), fclose(f), NULL;
	}

	p->name = (char *)calloc(name_len + 1, sizeof(char));
	if (p->name == NULL)
	{
		if (err_code)
			*err_code = FAIL_ALLOCATED_MEMORY;
		return destroy(&p), fclose(f), NULL;
	}

	fread(p->name, sizeof(char), name_len, f);

	check = fread(&surname_len, sizeof(unsigned int), 1, f);
	if (!check || feof(f))
	{
		if (err_code)
			*err_code = FILE_CORRUPTED;
		return destroy(&p), fclose(f), NULL;
	}

	p->surname = (char *)calloc(surname_len + 1, sizeof(char));
	if (p->surname == NULL)
	{
		if (err_code)
			*err_code = FAIL_ALLOCATED_MEMORY;
		return destroy(&p), fclose(f), NULL;
	}

	fread(p->surname, sizeof(char), surname_len, f);

	check = fread(&p->index, sizeof(int), 1, f);
	if (!check)
	{
		if (err_code)
			*err_code = FILE_CORRUPTED;
		return destroy(&p), fclose(f), NULL;
	}

	*(p->name + name_len) = '\0';
	*(p->surname + surname_len) = '\0';

	if (err_code)
		*err_code = SUCCESS;
	fclose(f);

	return p;
}

void show(const struct student_t *p)
{
	if (p == NULL)
		return;
	printf("%s %s, %d", p->name, p->surname, p->index);
}

int main()
{
	struct student_t *s;
	int error = 0;
	char wyb;
	char *filename;

	printf("Witaj wedrowcze, co chcesz zrobic?: ");
	scanf("%c", &wyb);

	while (getchar() != '\n');

	switch (wyb)
	{
	case 's':
	case 'S':

		s = read(&error);
		if (error == FAIL_ALLOCATED_MEMORY)
			return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

		if (error > 0 && error < 4)
			return printf("Incorrect input data"), 2;

		printf("Podaj nazwe pliku: ");
		filename = (char *)calloc(FILE_SIZE + 1, sizeof(char));
		if (filename == NULL)
			return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

		scanf("%39[^\n]", filename);
		int x = save_student_b(s, filename);

		if (x == 1 || x == 2)
			return destroy(&s), free(filename), printf("Couldn't create file"), 5;

		printf("File saved");
		free(filename);
		destroy(&s);

		break;

	case 'l':
	case 'L':

		filename = (char *)calloc(FILE_SIZE + 1, sizeof(char));
		if (filename == NULL)
			return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

		printf("Podaj nazwe pliku: ");
		scanf("%39s", filename);
		s = load_student_b(filename, &error);

		if (error > 0 && error < 3)
			return destroy(&s), free(filename), printf("Couldn't open file"), 4;

		else if (error == 3)
			return destroy(&s), free(filename), printf("File corrupted"), 6;

		else if (error == 4)
			return destroy(&s), free(filename), printf("Failed to allocate memory"), 8;

		show(s);
		free(filename);
		destroy(&s);

		break;

	default:
		return printf("Incorrect input"), INCORRECT_INPUT;
	}

	return 0;
}