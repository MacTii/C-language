#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define BLAD -1
#define INCORRECT_INPUT 1
#define COULDNT_OPEN_FILE 4
#define FILE_CORRUPTED 6
#define INCORRECT -1

struct point_t
{
	int x;
	int y;
};

float distance(const struct point_t *p1, const struct point_t *p2, int *err_code)
{
	if (p1 == NULL || p2 == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return BLAD;
	}
	float distance_p = sqrt(pow(((p2->x) - (p1->x)), 2) + pow(((p2->y) - (p1->y)), 2));
	if (err_code != NULL)
		*err_code = 0;
	return distance_p;
}

struct point_t *set(struct point_t *p, int x, int y)
{
	if (p == NULL)
		return NULL;
	p->x = x;
	p->y = y;
	return p;
}

int end_of_file(FILE *f)
{
	int now = ftell(f);
	fseek(f, 0, SEEK_END);
	int end = ftell(f);
	fseek(f, now, SEEK_SET);
	return end;
}

int read(struct point_t *p, FILE *f)
{
	if (p == NULL || f == NULL)
		return INCORRECT;
	int x, y;
	int z = fscanf(f, "%d %d", &x, &y);
	if (z != 2)
		return INCORRECT;
	char znak = getc(f);
	if (znak != '\n')
		fseek(f, -1, SEEK_CUR);
	if (!set(p, x, y))
		return INCORRECT;
	return 0;
}

void read_filename(char *filename, int size)
{
	int i;
	for (i = 0; i <= size; i++)
	{
		*(filename + i) = getchar();
		if (*(filename + i) == '\n')
		{
			*(filename + i) = '\0';
			break;
		}
		if (i + 1 == size)
			i--;
	}
}

int main()
{
	struct point_t p1, p2, m1, m2;
	char filename[100];
	float len1;
	printf("Podaj nazwe pliku:\n");
	read_filename(filename, 100);
	FILE *f = fopen(filename, "r");
	if (f == NULL)
		return printf("Couldn't open file"), COULDNT_OPEN_FILE;
	if (read(&p1, f) != 0)
	{
		printf("File corrupted");
		fclose(f);
		return FILE_CORRUPTED;
	}
	if (read(&p2, f) != 0)
	{
		printf("File corrupted");
		fclose(f);
		return FILE_CORRUPTED;
	}
	len1 = distance(&p1, &p2, NULL);
	set(&m1, p1.x, p1.y);
	set(&m2, p2.x, p2.y);
	fseek(f, 0, SEEK_SET);
	int now = ftell(f);
	while (now < end_of_file(f))
	{
		int first = ftell(f);
		fseek(f, first, SEEK_SET);
		if (read(&p1, f) != 0 && end_of_file(f) > ftell(f))
		{
			printf("File corrupted");
			fclose(f);
			return FILE_CORRUPTED;
		}
		else if (ftell(f) >= end_of_file(f))
			break;
		while (now < end_of_file(f))
		{
			if (read(&p2, f) != 0 && end_of_file(f) > ftell(f))
			{
				printf("File corrupted");
				fclose(f);
				return FILE_CORRUPTED;
			}
			else if (ftell(f) >= end_of_file(f))
				break;
			now = ftell(f);
			float len2 = distance(&p1, &p2, NULL);
			if (len2 < len1 && len2 > -1)
			{
				len1 = distance(&p1, &p2, NULL);
				set(&m1, p1.x, p1.y);
				set(&m2, p2.x, p2.y);
			}
			else if (len2 == len1)
			{
				if (p2.x < m2.x)
				{
					len1 = distance(&p1, &p2, NULL);
					set(&m1, p1.x, p1.y);
					set(&m2, p2.x, p2.y);
				}
			}
		}
		fseek(f, first, SEEK_SET);
		read(&p1, f);
		now = ftell(f);
	}
	printf("%d %d %d %d", m2.x, m2.y, m1.x, m1.y);
	fclose(f);
	return 0;
}