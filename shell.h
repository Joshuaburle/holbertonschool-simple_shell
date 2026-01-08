#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void print_not_found(char *av0, unsigned int count, char *cmd);
int execute_command(char *cmd, char *av0, unsigned int count);

#endif /* SHELL_H */
