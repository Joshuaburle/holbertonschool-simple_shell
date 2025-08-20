#include "shell.h"

/* Vérifie si c'est une commande intégrée (exit/env) */
int check_builtin(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		return (-1); /* Demande de sortie */
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1); /* Commande exécutée */
	}

	return (0); /* Pas une commande intégrée */
}

/* Affiche toutes les variables d'environnement */
void print_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
