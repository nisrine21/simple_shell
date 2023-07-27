#include "shell.h"
/**
 * _strtok - tokenizes a string using a set of delimiters
 *
 * @line: string to be tokenized
 * @delim: contains the delimiter characters
 * Return: A pointer to the next token in the line if
 * available or NULL if there are no more tokens left
*/
char *_strtok(char *line, char *delim)
{
	int i;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			break;
		}
		if (delim[i] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
