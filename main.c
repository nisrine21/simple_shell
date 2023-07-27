#include "shell.h"
/**
 * main - entry point of the program
 *
 * @argc: number of command line arguments
 * @argv: array of strings containing the command line arguments
 * @env: array of strings containing the program's env variables
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We're in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - signal handler for signint (ctrl+c)
 *
 * @UNUSED: the unused integer argument required by the signal handler
 */

void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - inicializes the data structure
 *
 * @data: pointer to the structure of data to be initialized
 * @argv: contains the command line arguments
 *@argc: the nulber of command line arguments
 * @env: contains the program's env variables
 */

void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int j = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[j]; j++)
		{
			data->env[j] = str_duplicate(env[j]);
		}
	}
	data->env[j] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (j = 0; j < 20; j++)
	{
		data->alias_list[j] = NULL;
	}
}

/**
 * sisifo - Main execution loop of the program
 *
 * @prompt: represents the prompt mesage to be displayed
 * @data: contains program data
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
