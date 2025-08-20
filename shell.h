#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

extern char **environ;

/* prompt + I/O */
void display_prompt(void);
char *read_line(void);
int is_empty_or_whitespace(char *line);

/* exec */
int execute_command(char *command, char *program_name);
char *find_command(const char *cmd);

/* split */
char **_split_line(char *line);
void free_tokens(char **tokens);

#endif /* SHELL_H */
