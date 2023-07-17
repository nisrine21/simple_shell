#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_OF_NIYOU 64
#define DELIMITERS " \t\r\n\a"

extern char **environ;

void prompt(char **av, char **env);


#endif /*SHELL_H*/
