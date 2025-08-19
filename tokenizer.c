#include "shell.h"

/**
 * _split_line - Divise une ligne de commande en arguments (tokens)
 * @line: La ligne de commande à diviser
 * Return: Tableau de pointeurs vers les arguments, ou NULL en cas d'erreur
 * 
 * Cette fonction implémente le parsing des commandes shell :
 * 1. Divise la ligne en tokens en utilisant les espaces comme séparateurs
 * 2. Alloue dynamiquement la mémoire pour chaque token
 * 3. Retourne un tableau terminé par NULL (comme argv)
 * 
 * Exemple : "ls -la /home" devient ["ls", "-la", "/home", NULL]
 * 
 * Note: Utilise strtok() qui modifie la chaîne originale, d'où la nécessité
 * de faire une copie de la ligne d'entrée
 */
char **_split_line(char *line)
{
    char *line_copy;      /* Copie de la ligne pour manipulation */
    char **tokens;        /* Tableau des tokens résultants */
    char *token;          /* Token individuel */
    int count = 0;        /* Nombre de tokens trouvés */
    int capacity = 10;    /* Capacité initiale du tableau (redimensionnable) */

    /* Vérification des paramètres d'entrée */
    if (line == NULL)
        return (NULL);

    /* Allocation initiale du tableau de tokens */
    tokens = malloc(capacity * sizeof(char *));
    if (tokens == NULL)
        return (NULL);  /* Erreur d'allocation mémoire */

    /* Copie de la ligne pour pouvoir la diviser avec strtok */
    line_copy = strdup(line);
    if (line_copy == NULL)
    {
        free(tokens);
        return (NULL);  /* Erreur d'allocation mémoire */
    }

    /* Division de la ligne en tokens en utilisant l'espace comme séparateur */
    token = strtok(line_copy, " \t\n");
    
    /* Traitement de chaque token trouvé */
    while (token != NULL)
    {
        /* Vérification si le tableau a besoin d'être agrandi */
        if (count >= capacity)
        {
            capacity *= 2;  /* Doublement de la capacité */
            char **new_tokens = realloc(tokens, capacity * sizeof(char *));
            
            if (new_tokens == NULL)
            {
                /* Erreur lors du redimensionnement - nettoyage et sortie */
                free_tokens(tokens);
                free(line_copy);
                return (NULL);
            }
            
            tokens = new_tokens;
        }

        /* Allocation et copie du token */
        tokens[count] = strdup(token);
        if (tokens[count] == NULL)
        {
            /* Erreur d'allocation - nettoyage et sortie */
            free_tokens(tokens);
            free(line_copy);
            return (NULL);
        }

        count++;  /* Passage au token suivant */
        
        /* Récupération du prochain token */
        token = strtok(NULL, " \t\n");
    }

    /* Ajout du marqueur de fin (NULL) pour terminer le tableau */
    tokens[count] = NULL;

    /* Libération de la copie de la ligne */
    free(line_copy);

    return (tokens);
}

/**
 * free_tokens - Libère la mémoire allouée pour un tableau de tokens
 * @tokens: Tableau de pointeurs vers les tokens à libérer
 * 
 * Cette fonction libère proprement la mémoire :
 * 1. Libère chaque token individuel
 * 2. Libère le tableau de pointeurs
 * 
 * Important : Cette fonction doit être appelée pour éviter les fuites mémoire
 * après chaque utilisation de _split_line()
 */
void free_tokens(char **tokens)
{
    int i;

    /* Vérification des paramètres d'entrée */
    if (tokens == NULL)
        return;

    /* Libération de chaque token individuel */
    for (i = 0; tokens[i] != NULL; i++)
    {
        free(tokens[i]);
    }

    /* Libération du tableau de pointeurs */
    free(tokens);
}
