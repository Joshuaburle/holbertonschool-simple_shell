#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

extern char **environ;

/* Function prototypes */
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
int handle_exit(char **argv);
int run_command(char *full_path, char **argv, char *program_name);
pid_t create_process(void);
int wait_for_child(pid_t pid);

#endif
