#ifndef SHELL_H
#define SHELL_H

/* Inclusion des bibliothèques système nécessaires */
#include <stdio.h>      /* Pour printf, fprintf, stderr */
#include <stdlib.h>     /* Pour malloc, free, exit */
#include <string.h>     /* Pour strcmp, strlen, strtok */
#include <unistd.h>     /* Pour fork, execve, access */
#include <sys/wait.h>   /* Pour wait, waitpid */
#include <sys/stat.h>   /* Pour stat, S_ISREG, X_OK */
#include <signal.h>     /* Pour signal, SIGINT */

/* Variables globales */
extern char **environ;  /* Pointeur vers les variables d'environnement du système */

/* ===== PROTOTYPES DES FONCTIONS ===== */

/**
 * sigint_handler - Gère le signal Ctrl+C (SIGINT)
 * @sig: Numéro du signal reçu
 * Affiche un nouveau prompt quand l'utilisateur appuie sur Ctrl+C
 */
void sigint_handler(int sig);

/**
 * display_prompt - Affiche le prompt du shell
 * Affiche "$ " pour indiquer que le shell attend une commande
 */
void display_prompt(void);

/**
 * read_line - Lit une ligne de commande depuis l'entrée standard
 * Return: Pointeur vers la ligne lue, ou NULL en cas d'erreur
 * Utilise getline() pour lire la commande entrée par l'utilisateur
 */
char *read_line(void);

/**
 * is_empty_or_whitespace - Vérifie si une ligne est vide ou ne contient que des espaces
 * @line: La ligne à vérifier
 * Return: 1 si la ligne est vide/espaces, 0 sinon
 * Évite d'exécuter des commandes vides
 */
int is_empty_or_whitespace(char *line);

/**
 * _split_line - Divise une ligne de commande en arguments (tokens)
 * @line: La ligne de commande à diviser
 * Return: Tableau de pointeurs vers les arguments, ou NULL en cas d'erreur
 * Utilise strtok() pour séparer les arguments par des espaces
 */
char **_split_line(char *line);

/**
 * execute_command - Fonction principale d'exécution des commandes
 * @command: La commande complète à exécuter
 * @program_name: Nom du programme shell (pour les messages d'erreur)
 * @line_num: Numéro de la ligne actuelle (pour les messages d'erreur)
 * Return: 1 pour continuer, 0 pour quitter le shell
 * 
 * Cette fonction :
 * 1. Vérifie si la commande est vide
 * 2. Divise la commande en arguments
 * 3. Gère les commandes intégrées (exit)
 * 4. Trouve le chemin de la commande externe
 * 5. Exécute la commande avec fork/execve
 */
int execute_command(char *command, char *program_name, int line_num);

/**
 * find_command - Trouve le chemin complet d'une commande dans le PATH
 * @command: Nom de la commande à rechercher
 * Return: Chemin complet de la commande, ou NULL si non trouvée
 * 
 * Recherche la commande dans tous les répertoires du PATH
 * Vérifie que le fichier existe et est exécutable
 */
char *find_command(char *command);

/**
 * file_exists - Vérifie si un fichier existe et est exécutable
 * @filepath: Chemin du fichier à vérifier
 * Return: 1 si le fichier existe et est exécutable, 0 sinon
 * Utilise access() avec X_OK pour vérifier les permissions d'exécution
 */
int file_exists(char *filepath);

/**
 * free_tokens - Libère la mémoire allouée pour un tableau de tokens
 * @tokens: Tableau de pointeurs vers les tokens à libérer
 * Libère chaque token puis le tableau lui-même
 */
void free_tokens(char **tokens);

/**
 * get_path_env - Récupère la variable d'environnement PATH
 * Return: Pointeur vers la valeur de PATH, ou NULL si non définie
 * Utilise getenv("PATH") pour récupérer le PATH système
 */
char *get_path_env(void);

/**
 * handle_exit - Gère la commande intégrée 'exit'
 * @argv: Tableau des arguments de la commande
 * Return: 0 pour quitter le shell, 1 pour continuer
 * 
 * Vérifie si la commande est 'exit' et quitte le shell
 * Libère la mémoire avant de quitter
 */
int handle_exit(char **argv);

/**
 * run_command - Exécute une commande externe avec fork et execve
 * @full_path: Chemin complet de la commande à exécuter
 * @argv: Tableau des arguments de la commande
 * @program_name: Nom du programme shell (pour les messages d'erreur)
 * Return: 1 en cas de succès, 0 en cas d'échec
 * 
 * Cette fonction :
 * 1. Crée un nouveau processus avec fork()
 * 2. Dans le processus enfant, exécute la commande avec execve()
 * 3. Dans le processus parent, attend la fin de l'exécution avec wait()
 */
int run_command(char *full_path, char **argv, char *program_name);

#endif
