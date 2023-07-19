#include "shell.h"
#include <stdio.h>


char *find_path(char *cmd,char **envp)
{
	UNUSED(cmd);
	char *path_env = NULL;
	char *path = NULL;
	char *full_path = NULL;
	int i;

	for (i = 0; envp[i] != NULL; i++)
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

void handle_env(char **nv)
{
	int i;

	for (i = 0; nv[i] != NULL; i++)
	{
		printf("%s\n", nv[i]);
	}
}

void tokenizeInput(char *string, char *argv[], size_t maxArgs)
{
	size_t j = 0;
	argv[j] = strtok(string, " ");
	while (argv[j] != NULL && j < maxArgs - 1)
	{
		j++;
		argv[j] = strtok(NULL, " ");
	}
	argv[j] = NULL;
}


void executeCmd(char *av[], char *nv[], char *argv[])
{
	pid_t ch_pid = fork();

	if (ch_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (ch_pid == 0)
	{
		char *cmd_path = find_path(argv[0], nv);
		if (cmd_path != NULL)
		{
			if (execve(cmd_path, argv, nv) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr, "%s: command not found\n", av[0]);
			exit(EXIT_FAILURE);
		}
	} else {
		int status;
		wait(&status);
	}
}

int main(int x, char **av, char **nv)
{
if (x == 1)
prompt(av, nv);
return (0);
}
