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
	int exit_code;

	/* Ignore les lignes vides */
	if (is_empty_or_whitespace(line))
	{
		free(line);
		return (0); /* Success for empty lines */
	}

	/* Exécute la commande */
	exit_code = execute_command(line, "hsh");

	/* Nettoie la mémoire */
	free(line);
	return (exit_code);
}

/**
 * main - Point d'entrée principal du shell
 * Return: 0 en cas de succès
 */
int main(void)
{
	char *line = NULL;
	int last_exit_code = 0;

	/* Configure la gestion de Ctrl+C */
	signal(SIGINT, sigint_handler);

	/* Boucle principale du shell */
	while (1)
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
		last_exit_code = process_command(line);
		line = NULL;
	}

	/* In non-interactive mode, return the last command's exit code */
	if (!isatty(STDIN_FILENO))
		return (last_exit_code);
	
	return (0);
}
