#include "shell.h"

/**
 * str_length - calculates the length of a null terminated string
 *
 * @string: string for which the length is to be determined
 * Return: length of the input string or 0 if string is NULL
 */
int str_length(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * str_duplicate - duplicates a nul terminated string
 *
 * @string: pointer to the null terlinated string to be duplicated
 * Return: pointer to the newly duplicated string or NULL
 */

char *str_duplicate(char *string)
{
	char *result;
	int length, j;

	if (string == NULL)
		return (NULL);

	length = str_length(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (j = 0; j < length ; j++)
	{
		result[j] = string[j];
	}

	return (result);
}

/**
 * str_compare - Compare two strings up to a specified number of ch
 *
 * @string1: first string to be compared
 * @string2: second string to be compared
 * @number: number of characters to compare
 * Return: 1 if the strings are equals,0 iotherwise.
 */

int str_compare(char *string1, char *string2, int number)
{
	int iterator;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0) /* infinite longitud */
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (iterator = 0; string1[iterator]; iterator++)
		{
			if (string1[iterator] != string2[iterator])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (string1[iterator] != string2[iterator])
			return (0);
		}
		return (1);
	}
}


/**
 * str_concat - concatenate two strings.
 *
 * @string1: first string
 * @string2: Second string
 * Return: pointer to the newly concatenated string
 */
char *str_concat(char *string1, char *string2)
{
	char *rslt;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = str_length(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = str_length(string2);

	rslt = malloc(sizeof(char) * (length1 + length2 + 1));
	if (rslt == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (length1 = 0; string1[length1] != '\0'; length1++)
		rslt[length1] = string1[length1];
	free(string1);

	/* copy of string2 */
	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		rslt[length1] = string2[length2];
		length1++;
	}

	rslt[length1] = '\0';
	return (rslt);
}

/**
 * str_reverse - reverses the characters ins a string in place
 *
 * @string: pointer to string to be reserved.
 * Return: void.
 */

void str_reverse(char *string)
{

	int j = 0, length = str_length(string) - 1;
	char hold;

	while (j < length)
	{
		hold = string[j];
		string[j++] = string[length];
		string[length--] = hold;
	}
}
