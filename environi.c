#include "shell.h"

/**
 * _myenv - Displays the current environment settings.
 * @infos: Parameterized structure designed
 * to uphold a consistent function prototype.
 * Return: Always 0
 */
int _myenv(infos_t *infos)
{
	print_list_str(infos->env);
	return (0);
}

/**
 * _getenv -Retrieves the value of an environment variable.
 * @infos: Container holding potential arguments,
 * utilized for maintaining consistency.
* @name: env var name
 *
 * Return: the value
 */
char *_getenv(infos_t *infos, const char *name)
{
	list_t *node = infos->env;
	char *n;

	while (node)
	{
		n = starts_with(node->str, name);
		if (n && *n)
			return (n);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Create a new environment variable
 * or update an existing one.
 * @infos: Parameterized structure designed
 * to uphold a consistent function prototype.
  *  Return: Always 0
 */
int _mysetenv(infos_t *infos)
{
	if (infos->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infos, infos->argv[1], infos->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Delete an environment variable.
 * @infos:  Parameterized structure designed
 * to uphold a consistent function prototype.
  * Return: Always 0
 */
int _myunsetenv(infos_t *infos)
{
	int i;

	if (infos->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= infos->argc; i++)
		_unsetenv(infos, infos->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @infos: Parameterized structure designed
 * to uphold a consistent function prototype.
  * Return: Always 0
 */
int populate_env_list(infos_t *infos)
{
	list_a *node = NULL;
	size_a i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	infos->env = node;
	return (0);
}

