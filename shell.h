#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

/* Variables globales */
extern char **environ;

/* Prototypes de fonctions */
void sigint_handler(int sig);
void display_prompt(void);
char *read_line(void);
int is_empty_or_whitespace(char *line);
char **_split_line(char *line);
int execute_command(char *command, char *program_name);
char *find_command(char *command);
int file_exists(char *filepath);
void free_tokens(char **tokens);
char *get_path_env(void);

#endif
