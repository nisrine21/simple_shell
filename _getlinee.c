#include "shell.h"

/**
* _getline - Retrieve a single line of input from the prompt.
* @data: struct for the program's data
*
* Return: reading counting bytes.
*/
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, f = 0;

	/* check if doesnot exist more commands in the array */
	/* and checks the logical operators */
	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if it exists */
		for (f = 0; array_commands[i]; f++)
		{
			free(array_commands[f]);
			array_commands[f] = NULL;
		}

		/* read from the file descriptor int to buff */
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* split lines for \n or ; */
		f = 0;
		do {
			array_commands[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));
			/*checks and split for && and || operators*/
			f = check_logic_ops(array_commands, f, array_operators);
		} while (array_commands[f++]);
	}

	/*obtains the next command (command 0) and remove it for the array*/
	data->input_line = array_commands[0];
	for (f = 0; array_commands[f]; f++)
	{
		array_commands[f] = array_commands[f + 1];
		array_operators[f] = array_operators[f + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - checks and split for && and || operators
* @array_commands: array of the commands.
* @i: index in the array_commands to be checked
* @array_operators: array of the logical operators for each previous command
*
* Return: index of the last command in the array_commands.
*/
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *tmp = NULL;
	int j;

	/* checks for the & char in the command line*/
	for (j = 0; array_commands[i] != NULL  && array_commands[i][j]; j++)
	{
		if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
		{
			/* split the line when chars && was found */
			tmp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(tmp + j + 2);
			i++;
			array_operators[i] = '&';
			free(tmp);
			j = 0;
		}
		if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		{
			/* split the line when chars || was found */
			tmp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(tmp + j + 2);
			i++;
			array_operators[i] = '|';
			free(tmp);
			j = 0;
		}
	}
	return (i);
}

