#include "shell.h"

/**
 * get_path_env - Récupère la variable d'environnement PATH
 * Return: Pointeur vers la valeur de PATH, ou NULL si non définie
 * 
 * Cette fonction utilise getenv("PATH") pour récupérer le chemin
 * des répertoires où le shell recherche les commandes
 */
char *get_path_env(void)
{
    return (getenv("PATH"));
}

/**
 * file_exists - Vérifie si un fichier existe et est exécutable
 * @filepath: Chemin du fichier à vérifier
 * Return: 1 si le fichier existe et est exécutable, 0 sinon
 * 
 * Cette fonction vérifie :
 * 1. L'existence du fichier
 * 2. Les permissions d'exécution (X_OK)
 * 
 * Utilise access() qui est plus efficace que stat() pour cette vérification
 */
int file_exists(char *filepath)
{
    /* Vérification de l'existence et des permissions d'exécution */
    if (access(filepath, X_OK) == 0)
        return (1);  /* Fichier existe et est exécutable */
    
    return (0);  /* Fichier inexistant ou non exécutable */
}

/**
 * find_command - Trouve le chemin complet d'une commande dans le PATH
 * @command: Nom de la commande à rechercher
 * Return: Chemin complet de la commande, ou NULL si non trouvée
 * 
 * Cette fonction implémente la recherche de commandes comme le fait bash :
 * 1. Récupère la variable d'environnement PATH
 * 2. Divise le PATH en répertoires individuels
 * 3. Teste chaque répertoire pour trouver la commande
 * 4. Vérifie que le fichier trouvé est exécutable
 * 
 * Exemple : si PATH="/usr/bin:/bin" et command="ls"
 * - Teste "/usr/bin/ls"
 * - Teste "/bin/ls"
 * - Retourne le premier chemin valide trouvé
 */
char *find_command(char *command)
{
    char *path_env;        /* Valeur de la variable PATH */
    char *path_copy;       /* Copie du PATH pour manipulation */
    char *dir;            /* Répertoire individuel du PATH */
    char *full_path;      /* Chemin complet à tester */
    size_t path_len;      /* Longueur du chemin complet */

    /* Récupération de la variable PATH */
    path_env = get_path_env();
    if (path_env == NULL)
        return (NULL);  /* PATH non défini */

    /* Copie du PATH pour pouvoir le diviser avec strtok */
    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return (NULL);  /* Erreur d'allocation mémoire */

    /* Division du PATH en répertoires individuels */
    dir = strtok(path_copy, ":");
    
    /* Test de chaque répertoire du PATH */
    while (dir != NULL)
    {
        /* Calcul de la longueur du chemin complet */
        path_len = strlen(dir) + strlen(command) + 2;  /* +2 pour "/" et "\0" */
        
        /* Allocation de mémoire pour le chemin complet */
        full_path = malloc(path_len);
        if (full_path == NULL)
        {
            free(path_copy);
            return (NULL);  /* Erreur d'allocation mémoire */
        }

        /* Construction du chemin complet : "répertoire/commande" */
        snprintf(full_path, path_len, "%s/%s", dir, command);

        /* Test si le fichier existe et est exécutable */
        if (file_exists(full_path))
        {
            free(path_copy);
            return (full_path);  /* Commande trouvée ! */
        }

        /* Libération de la mémoire pour ce chemin */
        free(full_path);
        
        /* Passage au répertoire suivant du PATH */
        dir = strtok(NULL, ":");
    }

    /* Libération de la mémoire et retour NULL si commande non trouvée */
    free(path_copy);
    return (NULL);
}
