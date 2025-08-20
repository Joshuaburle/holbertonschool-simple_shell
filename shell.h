#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void display_prompt(void);
char *read_line(void);
int is_empty_or_whitespace(char *line);
char **parse_command(char *command, int *argc);
int fork_and_exec(char *cmd_path, char **argv, char *program_name);
int execute_command(char *command, char *program_name);

#endif
