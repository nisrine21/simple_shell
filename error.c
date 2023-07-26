#include "shell.h"

/**
 * _eputs - prints a string to the standard output followed by newline
 *
 * @str: ponter to a string to be printed
 * Return: none (void)
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes a character to the standard error stream
 *
 * @x: The character to print
 * Return: 1 on success, or BUF_FLUSH to flush the buffer.
 */
int _eputchar(char x)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}

/**
 * _putfd - writes a character to the specified file descriptur with buff
 *
 * @x: caracter to be written
 * @fd: The file descriptor where the character will be written
 * Return: 1 indicating successful character writing
 */
int _putfd(char x, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}

/**
 * _putsfd - writes a string to the specified file desc with buff
 *
 * @str: pointer to a string to be written
 * @fd: The file descriptor where the character will be written
 * Return: the number of character successfully written
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
