#include "shell.h"

/**
 * long_to_string - converts a long integer num to a string
 *
 * @number: the long integer number to be converted
 * @string: buffer where the resulting string will be stored
 * @base: numerical base for the conversion
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}

/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to the input string to be converted.
 * Return: the converted integer value.
 */

int _atoi(char *s)
{
	int signe = 1;
	unsigned int number = 0;

	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			signe *= -1;
		if (*s == '+')
			signe *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * signe);
}

/**
 * count_characters - count the occurrences of character in a string.
 *
 * @string: pointer to string to be analyzed
 * @character: pointer to string sepresenting the character to count
 * Return: the total count of occurrences
 */

int count_characters(char *string, char *character)
{
	int j = 0, counter = 0;

	for (; string[j]; i++)
	{
		if (string[j] == character[0])
			counter++;
	}
	return (counter);
}
