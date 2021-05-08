#include <stdio.h>

#define N 40
#define FILE_SIZE 30
#define INCORRECT_INPUT 1
#define COULDNT_CREATE_FILE 5

struct byte_t
{
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
};

union bit_set
{
	char number;
	struct byte_t bit;
};

int main()
{
	union bit_set unia;
	unsigned int bmp[N];
	printf("Enter values:\n");
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 5; j++)
		{
			int x = scanf("%x", bmp + i * 5 + j);
			if (x != 1)
				return printf("Incorrect input"), INCORRECT_INPUT;
		}
	}
	char filename[FILE_SIZE + 1];
	printf("Podaj nazwe pliku:\n");
	scanf("%30s", filename);
	scanf("%*c");
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 5)
		{
			unia.number = *(bmp + i * 5 + j);
			if (unia.bit.b7)
				printf("#");
			else
				printf(" ");
			if (unia.bit.b6)
				printf("#");
			else
				printf(" ");
			if (unia.bit.b5)
				printf("#");
			else
				printf(" ");
			if (unia.bit.b4)
				printf("#");
			else
				printf(" ");
			if (unia.bit.b3)
				printf("#");
			else
				printf(" ");
			if (unia.bit.b2)
				printf("#");
			else
				printf(" ");
			if (unia.bit.b1)
				printf("#");
			else
				printf(" ");
			if (unia.bit.b0)
				printf("#");
			else
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
	FILE *f;
	f = fopen(filename, "w");
	if (f == NULL)
	{
		printf("Couldn't create file");
		return COULDNT_CREATE_FILE;
	}
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 5)
		{
			unia.number = *(bmp + i * 5 + j);
			if (unia.bit.b7)
				fprintf(f, "#");
			else
				fprintf(f, " ");
			if (unia.bit.b6)
				fprintf(f, "#");
			else
				fprintf(f, " ");
			if (unia.bit.b5)
				fprintf(f, "#");
			else
				fprintf(f, " ");
			if (unia.bit.b4)
				fprintf(f, "#");
			else
				fprintf(f, " ");
			if (unia.bit.b3)
				fprintf(f, "#");
			else
				fprintf(f, " ");
			if (unia.bit.b2)
				fprintf(f, "#");
			else
				fprintf(f, " ");
			if (unia.bit.b1)
				fprintf(f, "#");
			else
				fprintf(f, " ");
			if (unia.bit.b0)
				fprintf(f, "#");
			else
				fprintf(f, " ");
			j++;
		}
		fprintf(f, "\n");
		i++;
	}
	printf("File saved");
	fclose(f);
	return 0;
}