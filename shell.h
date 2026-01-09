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

/* path */
char *resolve_cmd(char *cmd, char *av0, unsigned int count, int *err_status);

/* errors */
void print_not_found(char *av0, unsigned int count, char *cmd);
void print_perm_denied(char *av0, unsigned int count, char *cmd);

/* builtins */
int handle_exit(char **argv, char *line, int last_status);
int handle_env(char **argv);

/* loop */
int process_line(char *line, char **av, unsigned int *count, int *last_status);
int shell_loop(char **av);

#endif /* SHELL_H */
