#include "shell.h"

/**
 * sigint_handler - Gère le signal Ctrl+C
 * @sig: Numéro du signal
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * main - Point d'entrée du shell
 * @argc: Nombre d'arguments
 * @argv: Tableau d'arguments
 * Return: 0 en cas de succès
 */
int main(int argc, char **argv)
{
	char *line;
	int status = 1;

	(void)argc;

	/* Configuration de la gestion du signal Ctrl+C */
	signal(SIGINT, sigint_handler);

	while (status)
	{
		/* Affichage du prompt en mode interactif */
		if (isatty(STDIN_FILENO))
			display_prompt();

		/* Lecture de la ligne de commande */
		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Exécution de la commande */
		status = execute_command(line, argv[0]);

		/* Nettoyage */
		free(line);
	}

	return (0);
}
