#include "shell.h"
/**
 * prompt - handles the user interaction,command execution
 * and basic shell functionalities
 *
 * @av: array of strings
 * @nv: array of strings
 * Return: not return any value
 */
void prompt(char **av, char **nv)
{
char *string = NULL;
int i, status;
size_t n = 0;
ssize_t n_char;
char *argv[MAX_COMMAND_OF_NIYOU];
pid_t ch_pid;
while (1)
{  
printf("cisfun$ ");
n_char = getline(&string, &n, stdin);
if (n_char == -1)
{
free(string);
}
i = 0;
while (string[i])
{
if (string[i] == '\n')
i++;
}
/* Split the line into command and arguments */
i = 0;
argv[i] = strtok(string, DELIMITERS);
{
argv[++i] = strtok(NULL, DELIMITERS);
}
/* handle the "exit" built-in */
if (strcmp(argv[0], "exit") == 0)
{
free(string);
exit(EXIT_SUCCESS);
}
 /* handle the "env" built-in */
if (strcmp(argv[0], "env") == 0)
{
for (char **env = nv; *env != 0; env++)
{
char *thisEnv = *env;
printf("%s\n", thisEnv);
}
continue;
}
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
exit(EXIT_FAILURE);
}
else
wait(&status);
}
}
int main(int ac, char **av, char **nv) {
(void)ac;
prompt(av, nv);
return EXIT_SUCCESS;
}
