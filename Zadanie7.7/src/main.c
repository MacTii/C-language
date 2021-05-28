#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>

#define EMPTY 0

struct point_t
{
	int x;
	int y;
};

int print_string(char *arg)
{
	if (!arg)
		return 0;

	int count = 0;
	for (int i = 0; *(arg + i) != '\x0'; i++, count++)
		putchar(*(arg + i));

	return count;
}

int print_int(int32_t arg)
{
	int count = 0;
	if (arg == 0)
	{
		putchar('0');
		count++;
	}

	if (arg < 0)
	{
		arg *= -1;
		putchar('-');
		count++;
	}

	int len = (int)log10(arg), power = 1;
	for (int i = 0; i < len + 1; i++)
	{
		for (int j = 0; j < len - i; j++)
			power *= 10;
		int number = arg / power;
		putchar((number % 10) + '0');
		count++;
		power = 1;
	}
	return count;
}

int print_double(double arg)
{
	int int_part, count = 0;

	//integer part
	if (arg > 0)
		int_part = (int)floor(arg);
	else
		int_part = (int)ceil(arg);

	count += print_int(int_part);

	//dot
	putchar('.');
	count++;

	//fractional part
	double power = 10;
	double f_part = arg > 0 ? arg - int_part : -1 * arg + int_part; // f_part = 28.35672 - 28 = 0.35672

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < i; j++)
			power *= 10;
		double number = f_part * power;
		putchar(((int)number % 10) + '0');
		count++;
		power = 10;
	}

	return count;
}

int print_point(struct point_t point)
{
	int count = 0;

	putchar('(');
	count++;

	count += print_int(point.x);

	putchar(' ');
	count++;

	count += print_int(point.y);

	putchar(')');
	count++;

	return count;
}

int my_printf(char *format, ...)
{
	if (!format)
		return EMPTY;

	bool check = false, check2 = true;
	int count = 0;

	va_list(ap);
	va_start(ap, format);

	for (int i = 0; *(format + i); i++)
	{
		if (check)
		{
			switch (*(format + i))
			{
			case 's':
				count += print_string(va_arg(ap, char *));
				check2 = false;
				break;

			case 'd':
				count += print_int(va_arg(ap, int32_t));
				check2 = false;
				break;

			case 'f':
				count += print_double(va_arg(ap, double));
				check2 = false;
				break;

			case 'p':
				count += print_point(va_arg(ap, struct point_t));
				check2 = false;
				break;
			}
		}
		if (*(format + i) == '%')
		{
			check = true;
			check2 = false;
		}
		if (check2)
		{
			putchar(*(format + i));
			count++;
		}
		check2 = true;
	}

	va_end(ap);
	return count;
}

//int scan_string(char* arg)
//{
//  int count = 0;
//  if (!arg)
//      return 0;
//}

int scan_int(int32_t *arg)
{
	if (!arg)
		return 0;

	int count = 0;

	int c;
	while (isspace(c = getchar()));
	ungetc(c, stdin);

	*arg = 0;
	bool is_negative = false, is_number = true, is_read = false; //, minus = false, zero = false; // -10

	while (1)
	{
		c = getchar();

		if (c == '\n' || c == ' ' || (!isdigit(c) && is_read))
			break;

		if (c == '-' && *arg == 0)
		{
			is_negative = true;
			//minus = true;
			continue;
		}

		//if (minus && c == '0') // after - number 0 like -032
		//{
		//  is_number = false;
		//  minus = false;
		//  continue;
		//}

		//if (c == '0' && *arg == 0) // after 0 some numbers like 023
		//{
		//  zero = true;
		//  continue;
		//}

		//if (zero && isdigit(c)) // up
		//{
		//  is_number = false;
		//  zero = false;
		//  continue;
		//}

		if (!isdigit(c))
			is_number = false;

		else
		{
			*arg *= 10;
			*arg += c - '0';
		}
		is_read = true;
	}

	if (is_negative)
		*arg *= -1;

	if (is_number)
		count++;

	return count;
}

int scan_double(double *arg)
{
	if (!arg)
		return 0;

	int count = 0, r_pos = 1, c;
	double power = 1.0;

	*arg = 0.0;

	while (isspace(c = getchar()));
	ungetc(c, stdin);

	bool is_negative = false, is_number = true, is_dot = false, is_read = false; // , minus = false, zero = false;

	while (1)
	{
		c = getchar();

		if (c == '\n' || c == ' ' || (!isdigit(c) && is_read && c != '.'))
			break;

		if (c == '-' && *arg == 0)
		{
			is_negative = true;
			//minus = true;
			continue;
		}

		//if (minus && c == '0') // after - number 0 like -032
		//{
		//  is_number = false;
		//  minus = false;
		//  continue;
		//}

		//if (c == '0' && *arg == 0) // after 0 some numbers like 023
		//{
		//  zero = true;
		//  continue;
		//}

		//if (zero && isdigit(c)) // up
		//{
		//  is_number = false;
		//  zero = false;
		//  continue;
		//}

		if (c == '.')
		{
			is_dot = true;
			continue;
		}

		if (!isdigit(c))
			is_number = false;

		else
		{
			if (!is_dot)
			{
				*arg *= 10;
				*arg += c - '0';
			}

			else
			{
				for (int i = 0; i < r_pos; i++)
					power *= 10;
				*arg += (double)(c - '0') / power;
				r_pos++;
				power = 1;
			}
		}

		is_read = true;
	}

	if (is_negative)
		*arg *= -1;

	if (is_number)
		count++;

	return count;
}

int scan_point(struct point_t *point)
{
	if (!point)
		return 0;

	int count = 0, c;

	while (isspace(c = getchar()));
	//ungetc(c, stdin);

	int tmp = 0;

	bool is_negative = false, is_number1 = true; //, minus = false, zero = false;

	if (c != '(')
		is_number1 = false;

	while (1) // (46, 69)
	{
		c = getchar();

		if (c == ' ')
			break;

		if (c == '-' && tmp == 0)
		{
			is_negative = true;
			//minus = true;
			continue;
		}

		//if (minus && c == '0') // after - number 0 like -032
		//{
		//  is_number = false;
		//  minus = false;
		//  continue;
		//}

		//if (c == '0' && tmp == 0) // after 0 some numbers like 023
		//{
		//  zero = true;
		//  continue;
		//}

		//if (zero && isdigit(c)) // up
		//{
		//  is_number = false;
		//  zero = false;
		//  continue;
		//}

		if (!isdigit(c))
			is_number1 = false;

		else
		{
			tmp *= 10;
			tmp += c - '0';
		}
	};

	if (is_negative)
		tmp *= -1;

	if (is_number1)
	{
		count++;
		point->x = tmp;
	}

	tmp = 0;
	is_negative = false; //, minus = false, zero = false;
	bool is_number2 = true;

	while (1) // (46, 69)
	{
		c = getchar();

		if (c == ')')
			break;

		if (c == '-' && tmp == 0)
		{
			is_negative = true;
			//minus = true;
			continue;
		}

		//if (minus && c == '0') // after - number 0 like -032
		//{
		//  is_number = false;
		//  minus = false;
		//  continue;
		//}

		//if (c == '0' && tmp == 0) // after 0 some numbers like 023
		//{
		//  zero = true;
		//  continue;
		//}

		//if (zero && isdigit(c)) // up
		//{
		//  is_number = false;
		//  zero = false;
		//  continue;
		//}

		if (!isdigit(c))
			is_number2 = false;

		else
		{
			tmp *= 10;
			tmp += c - '0';
		}
	};

	if (is_negative)
		tmp *= -1;

	point->y = tmp;

	if (c != ')')
		is_number2 = false;

	if (is_number1 && is_number2)
		count++;

	return count;
}

int my_scanf(char *format, ...)
{
	if (!format)
		return EMPTY;

	int check = false, count = 0;

	va_list(ap);
	va_start(ap, format);

	for (int i = 0; *(format + i); i++)
	{
		if (check)
		{
			switch (*(format + i))
			{
				/*case 's':
                count += scan_string(va_arg(ap, char*));
                break;*/

			case 'd':
				count += scan_int(va_arg(ap, int32_t *));
				break;

			case 'f':
				count += scan_double(va_arg(ap, double *));
				break;

			case 'p':
				count += scan_point(va_arg(ap, struct point_t *));
				break;
			}
		}
		if (*(format + i) == '%')
			check = true;
	}

	va_end(ap);
	return count;
}

int main()
{
	return 0;
}