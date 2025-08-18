#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <stddef.h>

/* Function prototypes */
void display_prompt(void);
char *read_line(void);
int is_empty_or_whitespace(char *line);
int execute_command(char *command, char *program_name);
char **_split_line(char *line);
void sigint_handler(int sig);

/* Global variables */
extern char **environ;

#endif
