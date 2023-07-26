#include "shell.h"

/**
 * get_environ - retrieves the env variables
 * from the structure and convert them into an array of strings
 *
 * @infos: Structure contains the env variable data
 * Return: pointer to an array of strings representing the env variables
 */
char **get_environ(infos_t *infos)
{
	if (!infos->environ || infos->env_changed)
	{
		infos->environ = list_to_strings(infos->env);
		infos->env_changed = 0;
	}
	return (infos->environ);
}

/**
 * _unsetenv - Removes an environment variable frm the list of env
 *
 * @infos: pointer to the structure that contains the list of env variables
 * @var: represent the name of the env variable to be removed
 * Return: integer indicating whether the operation was successful 1, or not 0.
 */
int _unsetenv(infos_t *infos, char *var)
{
	list_t *node = infos->env;
	size_t i = 0;
	char *a;

	if (!node || !var)
		return (0);
	while (node)
	{
		a = starts_with(node->str, var);
		if (a && *a == '=')
		{
			infos->env_changed = delete_node_at_index(&(infos->env), i);
			i = 0;
			node = infos->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (infos->env_changed);
}

/**
 * _setenv - Sets or updates an environment variable in the list
 *
 * @infos: contains the list of environment variabes
 * @var: represent the name of the env variable tos set or update
 * @value: represent the value to be assigned t the env variable
 * Return: integer indicating the success 0 or failure 1
 */
int _setenv(infos_t *infos, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *a;

	if (!var || !value)
		return (0);
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = infos->env;
	while (node)
	{
		a = starts_with(node->str, var);
		if (a && *a == '=')
		{
			free(node->str);
			node->str = buf;
			infos->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(infos->env), buf, 0);
	free(buf);
	infos->env_changed = 1;
	return (0);
}
