#include "shell.h"

/**
 * main - entry point of the simple shell program
 *
 * @x: number of command-line arguments
 * @av: array of strings
 * @nv: array of strings
 *
 * Return: 0 on success
 */

int main(int x, char **av, char **nv)
{
if (x == 1)
prompt(av, nv);
return (0);
}
