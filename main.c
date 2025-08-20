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
 * free_memory - Libère la mémoire allouée
 * @line: Ligne de commande
 * @args: Arguments de la commande
 * Return: void
 */
void free_memory(char *line, char **args)
{
	if (line)
		free(line);
	if (args)
		free_tokens(args);
}

/**
 * process_command - Traite une commande utilisateur
 * @line: Ligne de commande
 * Return: 1 pour continuer, 0 pour quitter
 */
int process_command(char *line)
{
	char **args = NULL;
	int status = 1;

	/* Ignore les lignes vides */
	if (is_empty_or_whitespace(line))
	{
		free(line);
		return (1);
	}

	/* Divise la ligne en arguments */
	args = _split_line(line);
	if (!args)
	{
		free(line);
		return (1);
	}

	/* Exécute la commande */
	status = execute_command(line, "hsh");

	/* Nettoie la mémoire */
	free_memory(line, args);
	return (status);
}

/**
 * main - Point d'entrée principal du shell
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

		/* Traite la commande */
		status = process_command(line);
		line = NULL;
	}

	return (0);
}
