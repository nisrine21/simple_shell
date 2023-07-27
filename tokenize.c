#include "shell.h"


/**
 * tokenize - separates a string into different
 * parts using a specified delimiter.
 *
 * @data: pointer to the program's data stucture
 * Return: an array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
	char *delim = " \t";
	int i, j, count = 2, length;

	length = str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (data->input_line[i] == delim[j])
				count++;
		}
	}

	data->tokens = malloc(count * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = str_duplicate(_strtok(data->input_line, delim));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = str_duplicate(_strtok(NULL, delim));
	}
}
