#include "shell.h"
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_COMMAND_OF_NIYOU 128

/**
 * find_path - find the full path of a command
 *  in the directories specified by the PATH environment variable.
 *
 *  @cmd: The name of the command to search for.
 *  @envp: An array of strings representing environment variables,
 *  including the PATH variable.
 *  Return: The full path of the command if found,
 *  or NULL if not found.
 */

char *find_path(char *cmd, char **envp)
{
	char *path_env = NULL;
	char *path = NULL;
	char *full_path = NULL;

	for (int i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
	}
	}
	if (path_env == NULL)
	{
		return (NULL);
	}
	path = strtok(path_env, ":");
	while (path != NULL)
	{
		size_t len = strlen(path) + strlen(cmd) + 2;

		full_path = (char *)malloc(len * sizeof(char));
		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		snprintf(full_path, len, "%s/%s", path, cmd);

		if (access(full_path, X_OK) == 0)
			{
				return (full_path);
			}
		free(full_path);

		path = strtok(NULL, ":");
}
return (NULL);
}

/**
 * handle_env - handle environment variables
 * @nv: An array of strings
 *
 * Return, void
 */
void handle_env(char **nv)
{
	for (int i = 0; nv[i] != NULL; i++)
	{
		printf("%s\n", nv[i]);
	}
}

/**
 * tokenizeInput - Tokenizes the user's command
 *
 * @string: The user's command string to be parsed.
 * @argv: An array of strings to store the parsed arguments.
 * @maxArgs: The maximum number of arguments that argv can hold.
 * Return: no return
 */
void tokenizeInput(char *string, char *argv[], size_t maxArgs)
{
	size_t j = 0;

	argv[j] = strtok(string, " ");
	while (argv[j] != NULL && j < maxArgs - 1)
	{
		j++;
		argv[j] = strtok(NULL, " ");
	}
	if (j == 0)
	{
		printf("No command entered.\n");
		return;
	}
	argv[j] = NULL;
}

/**
 * executeCmd - Execute a command
 *
 * @argv: The array of arguments
 * @av: The array of arguments
 * @nv: The array of arguments
 * Return: no return value
 */

void executeCmd(char *argv[], char *av[], char *nv[])
{
pid_t ch_pid;
char *path;
int status;
/* implement find_path function */
path = find_path(argv[0], nv);
if (path == NULL)
{
fprintf(stderr, "%s: command not found\n", av[0]);
return;
}
ch_pid = fork();
if (ch_pid == -1)
{
perror("fork");
free(path);
exit(EXIT_FAILURE);
}
else if (ch_pid == 0)
{
if (execve(path, argv, nv) == -1)
{
perror("execve");
free(path);
exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
}
free(path);
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
printf("cisfun$ ");
n_char = getline(&string, &n, stdin);
if (n_char == -1)
{
free(string);
exit(EXIT_FAILURE);
}


string[n_char - 1] = '\0';
tokenizeInput(string, argv, MAX_COMMAND_NIYOU);
executeCmd(av, nv, argv);
}
}

/**
 * main - entry point of the simple shell program
 *
 * @ac: number of command-line arguments
 * @av: array of strings
 * @nv: array of strings
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **nv)
{
(void)ac;
prompt(av, nv);
return (EXIT_SUCCESS);
}
