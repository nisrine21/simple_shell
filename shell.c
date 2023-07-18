#include "shell.h"

char *find_path(char *cmd)
{
/** Implement the logic to search for the command
 * in the paths specified in the "envp" array.
 * Return the full path of the command if found, or NULL if not found.
 * This function should handle searching through the directories
 * listed in the "PATH" environment variable.
 * You can use functions like "getenv" and "strtok" to accomplish this.
 * (Implementation is not provided here, as it depends
 * on the specific requirements of your shell.)
 */
	return NULL;
}

void handle_env(char **envp)
{
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
