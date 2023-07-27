#include "shell.h"

/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_variables(data_of_program *data)
{
	int r, t;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (r = 0; line[r]; r++)
		if (line[r] == '#')
			line[r--] = '\0';
		else if (line[r] == '$' && line[r + 1] == '?')
		{
			line[r] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + r + 2);
		}
		else if (line[r] == '$' && line[r + 1] == '$')
		{
			line[r] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + r + 2);
		}
		else if (line[r] == '$' && (line[r + 1] == ' ' || line[r + 1] == '\0'))
			continue;
		else if (line[r] == '$')
		{
			for (t = 1; line[r + t] && line[r + t] != ' '; t++)
				expansion[t - 1] = line[r + t];
			tmp = env_get_key(expansion, data);
			line[r] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + r + t);
			tmp ? buffer_add(line, tmp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(data_of_program *data)
{
	int r, t, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (r = 0; line[r]; r++)
	{
		for (t = 0; line[r + t] && line[r + t] != ' '; t++)
			expansion[t] = line[r + t];
		expansion[t] = '\0';

		tmp = get_alias(data, expansion);
		if (tmp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + r + t);
			line[r] = '\0';
			buffer_add(line, tmp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, k;

	length = str_length(buffer);
	for (k = 0; str_to_add[k]; k++)
	{
		buffer[length + k] = str_to_add[k];
	}
	buffer[length + k] = '\0';
	return (length + k);
}

