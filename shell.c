#include "shell.h"

/**
 * sigint_handler - Gère le signal Ctrl+C (SIGINT)
 * @sig: Numéro du signal reçu (non utilisé mais requis par la signature)
 * 
 * Cette fonction est appelée quand l'utilisateur appuie sur Ctrl+C.
 * Elle affiche un nouveau prompt sur une nouvelle ligne, permettant
 * à l'utilisateur de continuer à utiliser le shell.
 * 
 * Comportement : 
 * - Affiche une nouvelle ligne
 * - Affiche le prompt "$ "
 * - Permet à l'utilisateur de saisir une nouvelle commande
 */
void sigint_handler(int sig)
{
    (void)sig;  /* Variable non utilisée - évite le warning du compilateur */
    
    printf("\n");        /* Nouvelle ligne pour un affichage propre */
    display_prompt();    /* Affichage du prompt pour la prochaine commande */
}

/**
 * display_prompt - Affiche le prompt du shell
 * 
 * Cette fonction affiche le symbole "$ " qui indique que le shell
 * attend une commande de l'utilisateur.
 * 
 * Le prompt est affiché :
 * - Au démarrage du shell
 * - Après l'exécution de chaque commande
 * - Après l'interruption par Ctrl+C
 */
void display_prompt(void)
{
    printf("$ ");        /* Affichage du prompt standard */
    fflush(stdout);      /* Force l'affichage immédiat du prompt */
}

/**
 * read_line - Lit une ligne de commande depuis l'entrée standard
 * Return: Pointeur vers la ligne lue, ou NULL en cas d'erreur ou fin de fichier
 * 
 * Cette fonction utilise getline() pour lire une ligne complète depuis stdin.
 * Elle gère automatiquement l'allocation de mémoire et retourne :
 * - La ligne lue (avec le '\n' final)
 * - NULL en cas d'erreur ou de fin de fichier (Ctrl+D)
 * 
 * Important : La mémoire allouée par getline() doit être libérée par l'appelant
 * avec free() après utilisation.
 */
char *read_line(void)
{
    char *line = NULL;   /* Pointeur vers la ligne lue */
    size_t len = 0;      /* Longueur de la ligne (initialisée par getline) */
    ssize_t read;        /* Nombre de caractères lus */

    /* Lecture de la ligne avec getline */
    read = getline(&line, &len, stdin);
    
    /* Vérification du résultat de la lecture */
    if (read == -1)
    {
        /* Fin de fichier (Ctrl+D) ou erreur de lecture */
        free(line);      /* Libération de la mémoire allouée */
        return (NULL);
    }

    return (line);       /* Retour de la ligne lue */
}

/**
 * is_empty_or_whitespace - Vérifie si une ligne est vide ou ne contient que des espaces
 * @line: La ligne à vérifier
 * Return: 1 si la ligne est vide ou ne contient que des espaces, 0 sinon
 * 
 * Cette fonction vérifie si une ligne de commande est "vide" :
 * - Ligne NULL ou chaîne vide ""
 * - Ligne ne contenant que des espaces, tabulations ou retours à la ligne
 * 
 * Utilité : Évite d'exécuter des commandes vides qui pourraient causer des erreurs
 * ou des comportements inattendus.
 */
int is_empty_or_whitespace(char *line)
{
    int i;

    /* Vérification des cas évidents */
    if (line == NULL)
        return (1);  /* Ligne NULL = vide */

    /* Parcours de la ligne pour vérifier chaque caractère */
    for (i = 0; line[i] != '\0'; i++)
    {
        /* Si on trouve un caractère qui n'est pas un espace, tabulation ou retour à la ligne */
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (0);  /* Ligne non vide */
    }

    return (1);  /* Ligne vide ou ne contenant que des espaces */
}
