#include "shell.h"
/**
 * execute -Run a command using its full path along with environment variables.
 * @data: a pointer to the program's data
 * Return: If sucess returns zero, otherwise, return -1.
 */
int execute(data_of_program *data)
{
	int retvaly = 0, status;
	pid_t pidd;

	/* check for program in built ins */
	retvaly = builtins_list(data);
	if (retvaly != -1)/* if program was found in built ins */
		return (retvaly);

	/* check for program file system */
	retvaly = find_program(data);
	if (retvaly)
	{/* if program not found */
		return (retvaly);
	}
	else
	{/* if program was found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			retvaly = execve(data->tokens[0], data->tokens, data->env);
			if (retvaly == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}

