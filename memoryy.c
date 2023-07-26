#include "shell.h"

/**
 * bfree - safely memory pointed to by a pointer and set it to NULL
 *
 * @ptr: double pointer to the memory block
 * Return: returns 1 if freed successfully , otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
