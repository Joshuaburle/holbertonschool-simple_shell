#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

extern char **environ;

/* parsing */
char **parse_args(char *line);
void free_args(char **argv);

/* execution */
int execute_command(char **argv, char *av0, unsigned int count);

/* errors */
void print_not_found(char *av0, unsigned int count, char *cmd);
void print_perm_denied(char *av0, unsigned int count, char *cmd);

#endif /* SHELL_H */
