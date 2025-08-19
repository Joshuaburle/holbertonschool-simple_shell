#include "shell.h"

/**
 * handle_exit - Gère la commande intégrée 'exit'
 * @argv: Tableau des arguments de la commande
 * Return: 0 pour quitter le shell, 1 pour continuer
 * 
 * Cette fonction vérifie si la commande est 'exit' et :
 * - Libère la mémoire allouée pour les arguments
 * - Retourne 0 pour signaler au main() de quitter le shell
 * 
 * Note: Selon les spécifications du projet, on ne gère pas les arguments
 * de la commande exit - elle quitte simplement le shell
 */
int handle_exit(char **argv)
{
    /* Vérification si la commande est 'exit' */
    if (strcmp(argv[0], "exit") == 0)
    {
        /* Libération de la mémoire avant de quitter */
        free_tokens(argv);
        return (0);  /* Signal pour quitter le shell */
    }
    return (1);  /* Continuer l'exécution normale */
}

/**
 * run_command - Exécute une commande externe avec fork et execve
 * @full_path: Chemin complet de la commande à exécuter
 * @argv: Tableau des arguments de la commande
 * @program_name: Nom du programme shell (pour les messages d'erreur)
 * Return: 1 en cas de succès, 0 en cas d'échec
 * 
 * Cette fonction implémente le modèle fork-exec :
 * 1. Crée un nouveau processus avec fork()
 * 2. Dans le processus enfant, remplace le code avec execve()
 * 3. Dans le processus parent, attend la fin de l'exécution
 */
int run_command(char *full_path, char **argv, char *program_name)
{
    pid_t pid;    /* Identifiant du processus */
    int status;   /* Statut de sortie du processus enfant */

    /* Création d'un nouveau processus */
    pid = fork();
    if (pid == -1)
    {
        /* Erreur lors de la création du processus */
        perror("Error");
        return (0);
    }

    if (pid == 0)
    {
        /* Code exécuté dans le processus enfant */
        if (execve(full_path, argv, environ) == -1)
        {
            /* Erreur lors de l'exécution de la commande */
            perror(program_name);
            _exit(127);  /* Code d'erreur standard pour "command not found" */
        }
    }
    else
    {
        /* Code exécuté dans le processus parent */
        /* Attente de la fin de l'exécution du processus enfant */
        wait(&status);
    }

    return (1);  /* Succès de l'exécution */
}

/**
 * execute_command - Fonction principale d'exécution des commandes
 * @command: La commande complète à exécuter
 * @program_name: Nom du programme shell (pour les messages d'erreur)
 * @line_num: Numéro de la ligne actuelle (pour les messages d'erreur)
 * Return: 1 pour continuer, 0 pour quitter le shell
 * 
 * Cette fonction orchestre l'exécution des commandes :
 * 1. Vérifie si la commande est vide ou ne contient que des espaces
 * 2. Divise la commande en arguments (tokens)
 * 3. Gère les commandes intégrées (comme 'exit')
 * 4. Trouve le chemin de la commande externe dans le PATH
 * 5. Exécute la commande avec fork/execve
 * 6. Gère les erreurs avec les codes appropriés
 */
int execute_command(char *command, char *program_name, int line_num)
{
    char **argv;      /* Tableau des arguments de la commande */
    char *full_path;  /* Chemin complet de la commande */

    /* Vérification si la commande est vide ou ne contient que des espaces */
    if (command == NULL || is_empty_or_whitespace(command))
        return (1);  /* Continuer sans exécuter de commande */

    /* Division de la commande en arguments */
    argv = _split_line(command);
    if (argv == NULL || argv[0] == NULL)
        return (1);  /* Erreur lors de la division, continuer */

    /* Gestion des commandes intégrées (exit) */
    if (handle_exit(argv) == 0)
        return (0);  /* Quitter le shell */

    /* Recherche du chemin complet de la commande dans le PATH */
    full_path = find_command(argv[0]);
    if (full_path == NULL)
    {
        /* Commande non trouvée - affichage du message d'erreur */
        fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_num, argv[0]);
        free_tokens(argv);
        return (1);  /* Continuer malgré l'erreur */
    }

    /* Exécution de la commande externe */
    if (run_command(full_path, argv, program_name) == 0)
        return (0);  /* Erreur lors de l'exécution */

    /* Nettoyage de la mémoire */
    free_tokens(argv);
    free(full_path);
    
    return (1);  /* Continuer l'exécution normale */
}
