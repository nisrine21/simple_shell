#include "shell.h"
#include <sys/wait.h>

void prompt(char **av, char **nv)
{
	char *string = NULL;
	int i, status;
	size_t n = 0;
	ssize_t n_char;
	char *argv[] = {NULL, NULL};
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
		argv[0] = string;
		ch_pid = fork();
		if (ch_pid == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}
		if (ch_pid == 0)
		{
			if (execve(argv[0], argv, nv) == -1)
				printf("%s: No such file or directory\n", av[0]);
		}
		else
			wait(&status);
	}
}
