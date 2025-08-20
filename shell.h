#ifndef SHELL_H
#define SHELL_H

/* ===== INCLUSIONS SYSTÈME ===== */
#include <stdio.h>      /* printf, fprintf */
#include <stdlib.h>     /* malloc, free, exit */
#include <string.h>     /* strcmp, strdup, strtok */
#include <unistd.h>     /* access, execve, fork, getcwd */
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /* wait, waitpid */
#include <sys/stat.h>   /* stat, S_ISREG */
#include <signal.h>     /* signal, SIGINT */
#include <errno.h>      /* errno */

/* ===== VARIABLES GLOBALES ===== */
extern char **environ;  /* Tableau des variables d'environnement du système */

/* ===== PROTOTYPES DES FONCTIONS ===== */

/* === I/O ET PROMPT === */
void display_prompt(void);                    /* Affiche l'invite */
char *read_line(void);                        /* Lit ligne stdin */
int is_empty_or_whitespace(char *line);       /* Vérifie ligne vide */

/* === PARSING DES COMMANDES === */
char **_split_line(char *line);               /* Divise ligne */
char **resize_tokens(char **tokens, int position, int bufsize); /* Resize */
void free_tokens(char **tokens);              /* Libère tokens */

/* === COMMANDES INTÉGRÉES === */
void print_env(void);                         /* Affiche env */
int handle_builtin(char **argv, char *command_copy); /* Gère built-ins */

/* === GESTION DU PATH ET EXÉCUTION === */
char *find_command(const char *cmd);          /* Trouve commande */
int file_exists(char *filepath);              /* Vérifie existence */
int execute_command(char *command, char *program_name); /* Exécute */
int execute_fork(char *cmd_path, char **argv, char *cmd_copy);
int handle_command_not_found(char *program_name, char **argv, char *cmd_copy);

/* === UTILITAIRES === */
void write_error(char *prog, char *cmd, char *msg); /* Affiche erreur */
void free_memory(char *line, char **args);   /* Libère mémoire allouée */

#endif
