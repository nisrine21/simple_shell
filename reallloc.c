#include "shell.h"

/**
 * _memset - fill a block of memory with a specific byte value
 *
 * @a: the pointer to the memory block to be filled
 * @b: the byte value
 * @n: the nulber of bytes to be filled
 * Return: returns a pointer to the starting address of the memory block
 */
char *_memset(char *a, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		a[i] = b;
	return (a);
}

/**
 * ffree - free the memory pointed to
 * by a pointer to a pointer and set it to NULL
 *
 * @pp: pointer to a pointer to the memory block that needs ti be freed
 * Return: no value (void)
 */
void ffree(char **pp)
{
	char **c = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(c);
}

/**
 * _realloc - reallocates memory for a previously allocated block with new size
 *
 * @ptr: pointer to the previously allocated memory block
 * @o_size: the current size
 * @n_size: the new size
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
	char *a;

	if (!ptr)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr), NULL);
	if (n_size == o_size)
		return (ptr);
	a = malloc(n_size);
	if (!a)
		return (NULL);
	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		p[o_size] = ((char *)ptr)[o_size];
	free(ptr);
	return (a);
}
