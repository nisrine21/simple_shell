#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int a, b, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (a = 0; data->alias_list[a]; a++)
		{
			if (!alias || (str_compare(data->alias_list[a], alias, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (b = 0; data->alias_list[a][b]; b++)
				{
					buffer[b] = data->alias_list[a][b];
					if (data->alias_list[a][b] == '=')
						break;
				}
				buffer[b + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[a] + b + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int a, alias_length;

	/* validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (a = 0; data->alias_list[a]; a++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[a][alias_length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[a] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int a, b;
	char buffer[250] = {'0'}, *tmp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (a = 0; alias_string[a]; a++)
		if (alias_string[a] != '=')
			buffer[a] = alias_string[a];
		else
		{/* search if the value of the alias is another alias */
			tmp = get_alias(data, alias_string + a + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (b = 0; data->alias_list[b]; b++)
		if (str_compare(buffer, data->alias_list[b], a) &&
			data->alias_list[j][i] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[b]);
			break;
		}

	/* add the alias */
	if (tmp)
	{/* if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, tmp);
		data->alias_list[b] = str_duplicate(buffer);
	}
	else /* if the alias does not exist */
		data->alias_list[b] = str_duplicate(alias_string);
	return (0);
}

