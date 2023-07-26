#include "shell.h"

/**
 * list_len - counts the number of nodes in a linked list
 *
 * @a: pointer to first node
 * Return: size of list value
 */

size_t list_len(const list_t *a)
{
	size_t i = 0;

	while (a)
	{
		a = a->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - converts linked list to strings
 *
 * @head: pointer to the head of the linked list
 * Return: returns a pointer to an array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints the contents of a linked list
 *
 * @a: pointer to the head of the linked list
 * Return: size of list value
 */
size_t print_list(const list_t *a)
{
	size_t i = 0;

	while (a)
	{
		_puts(convert_number(a->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(a->str ? a->str : "(nil)");
		_puts("\n");
		a = a->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - searches for a node in a linked list
 *
 * @node: pointer to the head of linked list
 * @prefix: string to search for
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *a = NULL;

	while (node)
	{
		a = starts_with(node->str, prefix);
		if (a && ((c == -1) || (*a == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a specefic node
 *
 * @head: pointer to the head of linked list
 * @node: pointer to the node whose index is to be determined
 * Return: returns index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
