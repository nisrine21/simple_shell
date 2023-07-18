#include "shell.h"
#include <sys/wait.h>
void prompt(char **av, char **nv)
{
char *string = NULL;
int i, status;
size_t n = 0;
ssize_t n_char;
char *argv[MAX_COMMAND_OF_NIYOU];
pid_t ch_pid;
char *path;

while (1)
{
printf("cisfun$ ");
n_char = getline(&string, &n, stdin);
if (n_char == -1)
{
free(string);
exit(EXIT_SUCCESS);
}
i = 0;
while (string[i] != '\n' && string[i] != '\0')
{
i++;
}
string[i] = '\0';
i = 0;
argv[i] = strtok(string, " ");
while (argv[i] != NULL)
{
argv[++i] = strtok(NULL, " ");
}
path = argv[0];
if (argv[0][0] != '/')
{
path = find_path(argv[0]);
if (path == NULL)
{
fprintf(stderr, "%s: command not found\n", argv[0]);
continue;
}
}
ch_pid = fork();
if (ch_pid == -1)
{
perror(av[0]);
free(string);
exit(EXIT_FAILURE);        }
if (ch_pid == 0)
{
if (execve(path, argv, nv) == -1)
{
perror(av[0]);
}
exit(EXIT_FAILURE);
}
else
{
wait(&status);
}
}
}

