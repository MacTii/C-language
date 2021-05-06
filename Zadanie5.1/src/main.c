#include <stdio.h>
#include <stdlib.h>

#define FAIL_NAME 1
#define FAIL_SURNAME 2
#define FAIL_INDEX 3
#define FAIL_ALLOCATED_MEMORY 4
#define SUCCESS 0

#define INCORRECT_INPUT 1
#define FAILED_TO_ALLOCATE_MEMORY 8

#define INCORRECT 1
#define CORRECT_NAME 2
#define CORRECT_NAME_SURNAME 3
#define CORRECT_ALL 0

struct student_t
{
	char name[20];
	char surname[40];
	int index;
};

struct student_t *read(int *err_code)
{
	struct student_t *p = (struct student_t *)calloc(1, sizeof(struct student_t));
	if (p == NULL)
	{
		if (err_code)
			*err_code = FAIL_ALLOCATED_MEMORY;
		return printf("Failed to allocate memory"), NULL;
	}
	char space;
	int przecinek1 = 1;
	printf("Podaj dane:\n");
	int i;
	int koniec1 = 0;
	for (i = 0; i < 20; i++)
	{
		int x = scanf("%c", p->name + i);
		if (*(p->name + i) == ',')
		{
			koniec1 = 1;
			*(p->name + i) = '\0';
			break;
		}
		if (x != 1 || *(p->name + i) == '\n')
		{
			przecinek1 = 0;
			if (err_code != NULL)
				*err_code = INCORRECT;
			return free(p), NULL;
		}
	}
	if (koniec1 == 0)
	{
		if (err_code != NULL)
			*err_code = INCORRECT;
		return free(p), NULL;
	}
	int xx = scanf("%c", &space);
	if (xx != 1 && space != ' ')
	{
		if (err_code != NULL)
			*err_code = INCORRECT;
		return free(p), NULL;
	}
	int przecinek2 = 1;
	int koniec2 = 0;
	int j;
	for (j = 0; j < 40; j++)
	{
		int y = scanf("%c", p->surname + j);
		if (*(p->surname + j) == ',')
		{
			koniec2 = 1;
			*(p->surname + j) = '\0';
			break;
		}
		if (y != 1 || *(p->surname + j) == '\n')
		{
			przecinek2 = 0;
			if (przecinek1 == 0 && przecinek2 == 0)
			{
				if (err_code != NULL)
					*err_code = INCORRECT;
				return free(p), NULL;
			}
			if (err_code != NULL)
				*err_code = CORRECT_NAME;
			return free(p), NULL;
		}
	}
	if (koniec2 == 0)
	{
		if (err_code != NULL)
			*err_code = CORRECT_NAME;
		return free(p), NULL;
	}
	int yy = scanf("%c", &space);
	if (yy != 1 && space != ' ')
	{
		if (err_code != NULL)
			*err_code = INCORRECT;
		return free(p), NULL;
	}
	int z = scanf("%d", &p->index);
	if (z != 1)
	{
		if (err_code != NULL)
			*err_code = CORRECT_NAME_SURNAME;
		return free(p), NULL;
	}

	if (err_code != NULL)
		*err_code = CORRECT_ALL;
	return p;
}

void destroy(struct student_t **s)
{
	if (s == NULL || *s == NULL)
		return;
	free(*s);
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
	int err;

	s = read(&err);

	if (!!err && err < 4)
		return printf("Incorrect input"), err;

	if (err == 4)
		return 8;

	show(s);
	destroy(&s);

	return 0;
}