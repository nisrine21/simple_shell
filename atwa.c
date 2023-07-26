#include "shell.h"

/**
* interactive - checks if the program is running in an
* Interactive terminal session.
*
* @infos: pointer to a structure
* Return: 1 if running interactively, 0 otherwise.
*/

Int interactive(infos_t *infos)
{
	return (isatty(STDIN_FILENO) && infos->readfd <= 2);
}

/**
*is_delim -  Checks if a character is a delimiter by
* comparing it with characters in the delim string.
*
* @x: character to be checked.
* @delim: containing the delimiter characters.
* Return: 1 if the character is a delimiter, 0 otherwise.
*/
int is_delim(char x, char *delim)
{
	while (*delim)
		if (*delim++ == x)
			return (1);
	return (0);
}

/**
 * _isalpha - Checks if a character is an alphabetic character
 *
 * @x: The character to be checked.
 * Return: 1 if the character is an alphabetic, 0 otherwise.
 */
int _isalpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string of digits into an integer
 *
 * @a: containing the digits to be converted
 * Return: the integer value converted from the input string
 */
int _atoi(char *a)
{
	int j, signe = 1, flag = 0, output;
	unsigned int results = 0;

	for (j = 0; s[i] != '\0' && flag != 2; j++)
	{
		if (a[i] == '-')
			signe *= -1;
		if (a[i] >= '0' && a[i] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (a[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (signe == -1)
		output = -results;
	else
		output = results;
	return (output);
}
