
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define INCORRECT_INPUT 1
#define PLIK_NULLv1 2
#define PLIK_NULLv2 4
#define BLAD 3
#define INCORRECT_INPUT_DATA 2
#define COULDNT_OPEN_FILE 4
#define FILE_CORRUPTED 6
#define COULDNT_CREATE_FILE 5

union byte_t
{
	unsigned char number;
	struct bit_t
	{
		unsigned char b0 : 1;
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;
		unsigned char b5 : 1;
		unsigned char b6 : 1;
		unsigned char b7 : 1;
	} bit;
};

int decode(const char *input, const char *output)
{
	if (input == NULL || output == NULL)
		return INCORRECT_INPUT;
	union byte_t unia;
	FILE *inp_f, *out_f;
	inp_f = fopen(input, "r");
	if (inp_f == NULL)
		return PLIK_NULLv1;
	fseek(inp_f, 0, SEEK_END);
	int end = ftell(inp_f);
	if (end == 0)
	{
		fclose(inp_f);
		return BLAD;
	}
	if (end % 8 != 0)
	{
		fclose(inp_f);
		return BLAD;
	}
	fseek(inp_f, 0, 0);
	int i;
	char ch;
	for (i = 0; i < end; i++)
	{
		ch = fgetc(inp_f);
		if (ch != '1' && ch != '0')
		{
			fclose(inp_f);
			return BLAD;
		}
	}
	fseek(inp_f, 0, 0);
	out_f = fopen(output, "w");
	if (out_f == NULL)
	{
		fclose(inp_f);
		return PLIK_NULLv2;
	}
	unsigned char znak;
	for (i = 0; i < end / 8; i++)
	{
		znak = fgetc(inp_f);
		unia.bit.b7 = znak;
		znak = fgetc(inp_f);
		unia.bit.b6 = znak;
		znak = fgetc(inp_f);
		unia.bit.b5 = znak;
		znak = fgetc(inp_f);
		unia.bit.b4 = znak;
		znak = fgetc(inp_f);
		unia.bit.b3 = znak;
		znak = fgetc(inp_f);
		unia.bit.b2 = znak;
		znak = fgetc(inp_f);
		unia.bit.b1 = znak;
		znak = fgetc(inp_f);
		unia.bit.b0 = znak;
		znak = unia.number;
		fprintf(out_f, "%03d", znak);
	}
	fclose(inp_f);
	fclose(out_f);
	return 0;
}

int encode(const char *input, const char *output)
{
	if (input == NULL || output == NULL)
		return INCORRECT_INPUT;
	union byte_t unia;
	FILE *inp_f, *out_f;
	inp_f = fopen(input, "r");
	if (inp_f == NULL)
		return PLIK_NULLv1;
	fseek(inp_f, 0, SEEK_END);
	int end = ftell(inp_f);
	if (end == 0)
	{
		fclose(inp_f);
		return BLAD;
	}
	if (end % 3 != 0)
	{
		fclose(inp_f);
		return BLAD;
	}
	fseek(inp_f, 0, 0);
	int i;
	char ch = 0;
	for (i = 0; i < end; i++)
	{
		ch = fgetc(inp_f);
		if (!isdigit(ch))
		{
			fclose(inp_f);
			return BLAD;
		}
	}
	fseek(inp_f, 0, 0);
	int j, num = 0;
	for (i = 0; i < end; i += 3)
	{
		num = 0;
		for (j = 0; j < 3; j++)
		{
			ch = fgetc(inp_f);
			num = num * 10 + (ch - '0');
		}
		if (num > 255)
		{
			fclose(inp_f);
			return 3;
		}
	}
	fseek(inp_f, 0, 0);
	out_f = fopen(output, "w");
	if (out_f == NULL)
	{
		fclose(inp_f);
		return PLIK_NULLv2;
	}
	fseek(inp_f, 0, 0);
	num = 0;
	for (i = 0; i < end; i++)
	{
		for (j = 0; j < 3; j++)
		{
			ch = fgetc(inp_f);
			num = num * 10 + (ch - '0');
		}
		unia.number = num;
		fprintf(out_f, "%d%d%d%d%d%d%d%d", unia.bit.b7, unia.bit.b6, unia.bit.b5, unia.bit.b4, unia.bit.b3, unia.bit.b2, unia.bit.b1, unia.bit.b0);
		i += 2;
		num = 0;
	}
	fclose(inp_f);
	fclose(out_f);
	return 0;
}

int main()
{
	printf("Enter operation (D - bin to dec; E - dec to bin): ");
	char op;
	scanf("%c", &op);
	if (op != 'D' && op != 'd' && op != 'E' && op != 'e')
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;
	char out[31], inp[31];
	printf("Enter input file name: ");
	scanf("%30s", inp);
	setbuf(stdin, NULL);
	printf("Enter output file name: ");
	scanf("%30s", out);
	if (op == 'd' || op == 'D')
	{
		int x = decode(inp, out);
		switch (x)
		{
		case 2:
			return printf("Couldn't open file"), COULDNT_OPEN_FILE;
		case 3:
			return printf("File corrupted"), FILE_CORRUPTED;
		case 4:
			return printf("Couldn't create file"), COULDNT_CREATE_FILE;
		}
	}
	if (op == 'e' || op == 'E')
	{
		int x = encode(inp, out);
		switch (x)
		{
		case 2:
			return printf("Couldn't open file"), COULDNT_OPEN_FILE;
		case 3:
			return printf("File corrupted"), FILE_CORRUPTED;
		case 4:
			return printf("Couldn't create file"), COULDNT_CREATE_FILE;
		}
	}
	printf("File saved");
	return 0;
}
