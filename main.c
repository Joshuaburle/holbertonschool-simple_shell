#include "shell.h"

/**
 * sigint_handler - Gère le signal Ctrl+C
 * @sig: Numéro du signal
 * Return: void
 */
static void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(STDIN_FILENO))
		display_prompt();
}

/**
 * main - Point d'entrée principal du shell (Tâche 0.1)
 * Return: 0 en cas de succès
 */
int main(void)
{
	char *line = NULL;
	int status = 1;

	/* Configure la gestion de Ctrl+C */
	signal(SIGINT, sigint_handler);

	/* Boucle principale du shell */
	while (status)
	{
		/* Affiche le prompt si mode interactif */
		if (isatty(STDIN_FILENO))
			display_prompt();

		/* Lit la commande utilisateur */
		line = read_line();
		if (line == NULL) /* Ctrl+D détecté */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Ignore les lignes vides */
		if (is_empty_or_whitespace(line))
		{
			free(line);
			continue;
		}

		/* Exécute la commande simple (un seul mot) */
		status = execute_command(line, "shell");

		/* Nettoie la mémoire */
		free(line);
		line = NULL;

		/* Sort si exit demandé */
		if (status == 0)
			break;
	}

	return (0);
}
