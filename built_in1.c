#include "shell.h"

/**
 * _myhistory - prints the contents of linked list representing
 * the command history
 *
 * @infos:  pointer to a structure
 *  Return: always returns 0.
 */
int _myhistory(infos_t *infos)
{
	print_list(infos->history);
	return (0);
}

/**
 * unset_alias - removes an alias from a linked list of aliases
 *
 * @infos: ponter to a structure, containing the alias linked list.
 * @str:  represent the alias to be removed
 *
 * Return: 1 if the alias was successfully removd, 0 otherwise.
 */
int unset_alias(infos_t *infos, char *str)
{
	char *a, b;
	int ret;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	ret = delete_node_at_index(&(infos->alias),
		get_node_index(info->alias, node_starts_with(infos->alias, str, -1)));
	*a = b;
	return (ret);
}

/**
 * set_alias - adds or updates an alias in a linked of aliases.
 *
 * @infos: ponter to a structure, containing the alias linked list.
 * @str: represent the alias to be set.
 *
 * Return: 1 if the alias was successfully added or updated
 * otherwise
 */
int set_alias(infos_t *infos, char *str)
{
	char *a;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (unset_alias(infos, str));
	unset_alias(infos, str);
	return (add_node_end(&(infos->alias), str, 0) == NULL);
}


/**
 * print_alias -  this function prints an alias string
 *
 * @node: the alias node
 * Return: success 0, 1 error
 */
int print_alias(list_t *node)
{
	char *a = NULL, *b = NULL;

	if (node)
	{
		a = _strchr(node->str, '=');
		for (b = node->str; b <= a; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(a + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - handles the alias functionality
 *
 * @infos: contain command-line info and alias data
 *  Return: Always returns 0
 */
int _myalias(infos_t *infos)
{
	int i = 0;
	char *a = NULL;
	list_t *node = NULL;

	if (infos->argc == 1)
	{
		node = infos->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; infos->argv[i]; i++)
	{
		a = _strchr(infos->argv[i], '=');
		if (a)
			set_alias(infos, infos->argv[i]);
		else
			print_alias(node_starts_with(infos->alias, infos->argv[i], '='));
	}
	return (0);
}
