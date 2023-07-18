#include "sell.h"
#include <sys/wait.h>

#define MAX_COMMAND_NIYOU 100 /*max number of cmd to be runn*/

void prompt(char **av, char **nv)
{
	char *string = NULL;
	int i, j, status;
	size_t n = 0;
	ssize_t n_char;
	char *argv[MAX_COMMAND_NIYOU];
	pid_t ch_pid;

	while (1)
	{  /*display the prompt*/
		printf("cisfun$ ");
		/*read user's cmd*/
		n_char = getline(&string, &n, stdin);
		if (n_char == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (string[i])
		{
			if (string[i] == '\n')
				string[i] = 0;
			i++;
		}
		j = 0;
		argv[j] = strtok(string, " ");
		while (argv[j] != NULL && j < MAX_COMMAND_NIYOU - 1)
		{
			j++;
			argv[j] = strtok(NULL, " ");
		}
		argv[j] = NULL;
		ch_pid = fork();
		if (ch_pid == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}
		if (ch_pid == 0)
		{
			if (execve(argv[0], argv, nv) == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
				free(string);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}
}
