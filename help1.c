#include "shell.h"

/**
 * free_recurrent_data - frees memory allocated for recurrent data
 *
 * @data: contains program data
 * Return: None (void)
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - frees all dynalically allocated memory
 *
 * @data: contains program data
 * Return: None (void)
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees memory allocated for an array
 *
 * @array: pointer to the array of pointers to strings
 * Return: none (void)
 */
void free_array_of_pointers(char **array)
{
	int j;

	if (array != NULL)
	{
		for (j = 0; array[j]; j++)
			free(array[j]);

		free(array);
		array = NULL;
	}
}
