#include "shell.h"

/**
 * main - Point d'entrée principal du shell simple
 * @argc: Nombre d'arguments de ligne de commande
 * @argv: Tableau des arguments de ligne de commande
 * Return: 0 en cas de succès, 1 en cas d'erreur
 * 
 * Cette fonction :
 * 1. Configure la gestion des signaux (Ctrl+C)
 * 2. Lance la boucle principale du shell
 * 3. Gère les erreurs et la sortie propre du programme
 */
int main(int argc, char *argv[])
{
    char *line;
    int status = 1;
    static int line_count = 1;  /* Compteur de lignes pour les messages d'erreur */

    (void)argc;  /* Paramètre non utilisé - évite le warning du compilateur */

    /* Configuration du gestionnaire de signal pour Ctrl+C */
    signal(SIGINT, sigint_handler);

    /* Boucle principale du shell */
    while (status)
    {
        /* Affichage du prompt et lecture de la commande */
        display_prompt();
        line = read_line();

        /* Vérification de la fin de fichier (Ctrl+D) */
        if (line == NULL)
        {
            printf("\n");  /* Nouvelle ligne pour un affichage propre */
            break;
        }

        /* Exécution de la commande avec le numéro de ligne actuel */
        status = execute_command(line, argv[0], line_count);
        
        /* Libération de la mémoire de la ligne lue */
        free(line);
        
        /* Incrémentation du compteur de lignes pour la prochaine commande */
        line_count++;
    }

    return (0);
}
