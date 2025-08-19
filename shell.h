#ifndef SHELL_H
#define SHELL_H

/* Constantes */
#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64
#define PROMPT "#cisfun$ "

/* Structures */
typedef struct shell_info
{
	char *program_name;
	char **env;
	int exit_status;
} shell_info_t;

/* Prototypes des fonctions principales */
void shell_loop(char **env);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args, char **env, char *program_name);
void print_error(char *program_name);

/* Fonctions utilitaires */
void free_args(char **args);
int is_builtin(char *command);
void handle_builtin(char **args, shell_info_t *info);

#endif /* SHELL_H */
