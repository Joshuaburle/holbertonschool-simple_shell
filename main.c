#include "shell.h"

/* Gère Ctrl+C - réaffiche le prompt */
static void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(STDIN_FILENO))
		display_prompt();
}

/* Libère la mémoire allouée */
void free_memory(char *line, char **args)
{
	if (line)
		free(line);
	if (args)
		free_tokens(args);
}

/* Point d'entrée principal du shell */
int main(void)
{
	char *line = NULL;
	char **args = NULL;
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

		/* Divise la ligne en arguments */
		args = _split_line(line);
		if (!args)
		{
			free(line);
			continue;
		}

		/* Exécute la commande */
		status = execute_command(line, "shell");

		/* Nettoie la mémoire */
		free_memory(line, args);
		line = NULL;
		args = NULL;

		/* Sort si exit demandé */
		if (status == 0)
			break;
	}

	return (0);
}
