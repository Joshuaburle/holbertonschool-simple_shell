#include "shell.h"

/**
 * builtin_exit - Exécute la commande intégrée exit
 * @args: Tableau d'arguments
 * @prog_name: Nom du programme
 * Return: 0 pour quitter le shell
 */
int builtin_exit(char **args, char *prog_name)
{
	(void)args;
	(void)prog_name;
	return (0); /* Quitte le shell */
}

/**
 * builtin_env - Exécute la commande intégrée env
 * @args: Tableau d'arguments
 * @prog_name: Nom du programme
 * Return: 0 en cas de succès
 */
int builtin_env(char **args, char *prog_name)
{
	int i;

	(void)args;
	(void)prog_name;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (0);
}
