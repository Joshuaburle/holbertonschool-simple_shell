#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>

/* Function prototypes */
int shell_loop(char *program_name);
int execute_command(char *command, char *program_name);
char **_split_line(char *line);
char *find_command(char *command);

/* Global variables */
extern char **environ;

#endif
