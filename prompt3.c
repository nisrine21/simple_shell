#include "shell.h"
#include <sys/wait.h>

#define MAX_COMMAND_OF_NIYOU 128
#define DELIMITERS " \t\r\n\a"
/**
 * parse_command - Parse a command into arguments
 * @string: The command string to parse
 * @argv: The array to store the parsed arguments
 *
 * Return: A pointer to the array of arguments
 */
char **parse_command(char *string, char **argv)
{
int i = 0;
argv[i] = strtok(string, DELIMITERS);
while (argv[i] != NULL)
{
argv[++i] = strtok(NULL, DELIMITERS);
}
return (argv);
}
/**
 * execute_command - Execute a command
 * @argv: The array of arguments
 * @av: The array of arguments
 * @nv: The array of arguments
 */
void execute_command(char **argv, char **av, char **nv)
{
pid_t ch_pid;
char *path;
int status;
/* implement find_path function */
path = find_path(argv[0]);
if (path == NULL)
{
fprintf(stderr, "%s: command not found\n", argv[0]);
return;
}
ch_pid = fork();
if (ch_pid == -1)
{
perror(av[0]);
exit(EXIT_FAILURE);
}
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
/**
 * prompt - Prompt the user for a command
 * @av: The array of arguments
 * @nv: The array of arguments
 */
void prompt(char **av, char **nv)
{
char *string;
size_t n = 0;
ssize_t n_char;
char **argv = malloc(sizeof(char *) * MAX_COMMAND_OF_NIYOU);
while (1)
{
printf("cisfun$ ");
n_char = getline(&string, &n, stdin);
if (n_char == -1)
{
free(string);
exit(EXIT_SUCCESS);
}
argv = parse_command(string, argv);
if (strcmp(argv[0], "exit") == 0)
{
free(string);
exit(EXIT_SUCCESS);
}
if (strcmp(argv[0], "env") == 0)
{
/* implement handle_env function */
handle_env(nv);
continue;
}
execute_command(argv, av, nv);
}
}
/**
 * main - The main function of the shell
 * @ac: The count of arguments
 * @av: The array of arguments
 * @nv: The array of arguments
 *
 * Return: EXIT_SUCCESS on successful exit
 */
int main(int ac, char **av, char **nv)
{
(void)ac;
prompt(av, nv);
return (EXIT_SUCCESS);
}
