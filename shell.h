#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

/* Prototypes des fonctions */
void display_prompt(void);
char *read_line(void);
char **split(char *line);
int execute_command(char *command, char *program_name);
void sigint_handler(int sig);

/* Variables globales */
extern char **environ;

#endif
