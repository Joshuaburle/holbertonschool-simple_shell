#include "shell.h"

/* Gère Ctrl+C (réaffiche le prompt) */
static void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(STDIN_FILENO))
		display_prompt();
}

int main(int argc, char **argv)
{
	char *line = NULL;
	int status = 1;

	(void)argc;

	/* Configurer la gestion du signal Ctrl+C */
	signal(SIGINT, sigint_handler);

	while (status)
	{
		/* Afficher le prompt en mode interactif */
		if (isatty(STDIN_FILENO))
			display_prompt();

		/* Lire la ligne de commande */
		line = read_line();
		if (line == NULL) /* Ctrl+D ou EOF */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Exécuter la commande */
		status = execute_command(line, argv[0]);

		/* Nettoyer la mémoire */
		free(line);
		line = NULL;

		if (status == 0)
			break;
	}
	return (0);
}
