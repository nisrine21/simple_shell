#include "shell.h"

/**
 * _erratoi - Parses a string and converts it into an integer.
 * @d: The string that needs to be converted.
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _erratoi(char *d)
{
	int i = 0;
	unsigned long int result = 0;

	if (*d == '+')
		d++;  /* TODO: why does this make main return 255? */
	for (i = 0;  d[i] != '\0'; i++)
	{
		if (d[i] >= '0' && d[i] <= '9')
		{
			result *= 10;
			result += (d[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @infos: The parameters and return information in the form of a struct.
 * @estr: A string containing the specified error type.
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(infos_t *infos, char *estr)
{
	_eputs(infos->fname);
	_eputs(": ");
	print_d(infos->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infos->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - The function that outputs a decimal (integer) number in base 10.
* @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int abs, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		abs = -input;
		__putchar('-');
		count++;
	}
	else
		abs = input;
	current = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flag: argument flag
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: The memory address of the string that needs to be modified.
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

