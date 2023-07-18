#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_OF_NIYOU 100
#define MAX_COMMAND_NIYOU

/* Function prototypes*/ 
void tokenizeInput(char *string, char *argv[], size_t maxArgs);
void executeCmd(char *av[], char *nv[], char *argv[]);
void prompt(char **av, char **nv);


#endif /*SHELL_H*/
