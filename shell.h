#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Function prototypes */
void display_prompt(void);
char *read_line(void);
int execute_command(char *command);

/* Global variables */
extern char **environ;

#endif
