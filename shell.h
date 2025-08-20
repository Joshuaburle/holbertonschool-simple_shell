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
void display_prompt(void);                    /* Affiche l'invite #cisfun$ */
char *read_line(void);                        /* Lit une ligne depuis stdin */
int is_empty_or_whitespace(char *line);       /* Vérifie si ligne vide/espaces */

/* === PARSING DES COMMANDES === */
char **_split_line(char *line);               /* Divise ligne en tableau d'arguments */
void free_tokens(char **tokens);              /* Libère mémoire des tokens */

/* === COMMANDES INTÉGRÉES === */
void print_env(void);                         /* Affiche l'environnement */

/* === GESTION DU PATH ET EXÉCUTION === */
char *find_command(const char *cmd);          /* Trouve chemin complet d'une commande */
int file_exists(char *filepath);              /* Vérifie si fichier existe et exécutable */
int execute_command(char *command, char *program_name); /* Exécute une commande */

/* === UTILITAIRES === */
void free_memory(char *line, char **args);   /* Libère mémoire allouée */

#endif
