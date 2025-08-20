#include "shell.h"

/**
 * execute_command - exécute une ligne de commande avec arguments
 * Règles projet 0.2 : pas de PATH, seulement chemins absolus/relatifs.
 * Built-in géré : exit (sans arguments).
 *
 * Return: 1 pour continuer, 0 pour quitter
 */
int execute_command(char *command, char *program_name)
{
	pid_t pid;
	int status;
	char **argv = NULL;
	char *full_path = NULL;

	(void)program_name;

	if (!command || is_empty_or_whitespace(command))
		return 1;

	argv = _split_line(command);
	if (!argv || !argv[0])
	{
		free_tokens(argv);
		return 1;
	}

	/* built-in: exit (0.2: sans arguments) */
	if (strcmp(argv[0], "exit") == 0)
	{
		free_tokens(argv);
		return 0;
	}

	/* Trouver le chemin complet (sans PATH) */
	full_path = find_command(argv[0]);
	if (!full_path)
	{
		dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", argv[0]);
		free_tokens(argv);
		return 1;
	}

	if (access(full_path, X_OK) != 0)
	{
		dprintf(STDERR_FILENO, "./hsh: 1: %s: Permission denied\n", argv[0]);
		free(full_path);
		free_tokens(argv);
		return 1;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		free_tokens(argv);
		return 1;
	}
	if (pid == 0)
	{
		/* Enfant : lance le programme */
		execve(full_path, argv, environ);
		/* Si on arrive ici => erreur execve */
		dprintf(STDERR_FILENO, "./hsh: 1: %s: %s\n", argv[0], strerror(errno));
		_exit(2);
	}
	else
	{
		/* Parent : attend l'enfant */
		waitpid(pid, &status, 0);
	}

	free(full_path);
	free_tokens(argv);
	return 1;
}
