#include "shell.h"

/**
 * handle_exit - Gère la commande exit
 * @argv: Tableau des arguments
 * Return: 0 pour quitter, 1 pour continuer
 */
int handle_exit(char **argv)
{
	if (strcmp(argv[0], "exit") == 0)
	{
		free_tokens(argv);
		return (0);
	}
	return (1);
}

/**
 * run_command - Exécute une commande avec fork et execve
 * @full_path: Chemin complet de la commande
 * @argv: Tableau des arguments
 * @program_name: Nom du programme shell
 * Return: 1 en cas de succès, 0 en cas d'échec
 */
int run_command(char *full_path, char **argv, char *program_name)
{
	pid_t pid;

	pid = create_process();
	if (pid == -1)
	{
		free_tokens(argv);
		free(full_path);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(full_path, argv, environ) == -1)
		{
			perror(program_name);
			free_tokens(argv);
			free(full_path);
			_exit(127);
		}
	}
	else
	{
		wait_for_child(pid);
	}

	return (1);
}

/**
 * execute_command - Exécute une commande
 * @command: La commande à exécuter
 * @program_name: Nom du programme shell (argv[0])
 * Return: 1 pour continuer, 0 pour quitter
 */
int execute_command(char *command, char *program_name, int line_num)
{
	char **argv;
	char *full_path;

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

	argv = _split_line(command);
	if (argv == NULL || argv[0] == NULL)
		return (1);

	if (handle_exit(argv) == 0)
		return (0);

	full_path = find_command(argv[0]);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_num, argv[0]);
		free_tokens(argv);
		return (1);
	}

	if (run_command(full_path, argv, program_name) == 0)
		return (0);

	free_tokens(argv);
	free(full_path);
	return (1);
}
