#include "shell.h"

/**
 **_strncpy - copies at most n characters from src to dest
 *
 *@dest: ponter to the destination buffer
 *@src: pointer to the source
 *@n: max number of characters to be copied
 *Return: pointer to the destination buffer
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *a = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (a);
}

/**
 **_strncat - appends at most n characters from src to dest
 *
 *@dest: ponter to the destination buffer
 *@src: pointer to the source
 *@n:  max number of characters to be aooended
 *Return: pointer to the destination buffer
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *a = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (a);
}

/**
 **_strchr - searches for the first occurrence of the character
 *
 *@a: the pointer to the string where the search will be performed
 *@b: caracter to search for in the string
 *Return:  a pointer to the first occurrence, or NULL if is not found
 */
char *_strchr(char *a, char b)
{
	do {
		if (*a == b)
			return (a);
	} while (*a++ != '\0');
	return (NULL);
}
