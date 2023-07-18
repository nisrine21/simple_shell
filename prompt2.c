#include "shell.h"
#include <sys/wait.h>


/**
 * tokenizeInput - Tokenizes the user's command
 * string and stores individual arguments in argv.
 *
 * @string: The user's command string to be parsed.
 * @argv: An array of strings to store the parsed arguments.
 * @maxArgs: The maximum number of arguments that argv can hold.
 * Return: no return
 */

void tokenizeInput(char *string, char *argv[], size_t maxArgs)
{
	int j = 0;

	argv[j] = strtok(string, " ");
	while (argv[j] != NULL && j < maxArgs - 1)
{
	j++;
	argv[j] = strtok(NULL, " ");
}
argv[j] = NULL;
}

/**
 * executeCmd - Executes the given command in a child
 * process and waits for the child process to finish.
 *
 * @av: Array of strings representing command-line arguments.
 * @nv: Array of strings representing environment variables.
 * @argv: An array of strings containing the command and its arguments.
 * Return: no return
 */

void executeCmd(char *av[], char *nv[], char *argv[])
{
	pid_t ch_pid = fork();

	if (ch_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (ch_pid == 0)
	{
		if (execve(argv[0], argv, nv) == -1)
	i	{
			printf("%s: No such file or directory\n", av[0]);
			exit(EXIT_FAILURE);
		}
	} else
	{
		int status;

		wait(&status);
	}
}

/**
 * prompt - handles the user interaction, command execution
 * and basic shell functionalities
 *
 * @av: array of strings
 * @nv: array of strings
 * Return: not return any value
 */

void prompt(char **av, char **nv)
{
	char *string = NULL;
	size_t n = 0;
	ssize_t n_char;
	char *argv[MAX_COMMAND_NIYOU];

	while (1)
	{
		/* Display the prompt*/
		printf("cisfun$ ");
		/* Read user's command*/
		n_char = getline(&string, &n, stdin);
		if (n_char == -1)
	{
		free(string);
		exit(EXIT_FAILURE);
	}
		/* Remove newline character*/
		string[n_char - 1] = '\0';
		tokenizeInput(string, argv, MAX_COMMAND_NIYOU);
		executeCmd(av, nv, argv);
	}
	free(string);
}
