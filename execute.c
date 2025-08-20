#include "shell.h"

/**
 * create_process - Crée un nouveau processus enfant
 * Return: PID du processus créé, ou -1 en cas d'échec
 */
pid_t create_process(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

/**
 * wait_for_child - Attend que le processus enfant se termine
 * @pid: PID du processus à attendre
 * Return: 0 en cas de succès, -1 en cas d'échec
 */
int wait_for_child(pid_t pid)
{
	int status;

	(void)pid;
	if (wait(&status) == -1)
	{
		perror("wait");
		return (-1);
	}
	return (0);
}

/**
 * handle_command_execution - Gère l'exécution d'une commande
 * @full_path: Chemin complet de la commande
 * @argv: Arguments de la commande
 * @program_name: Nom du programme shell
 * Return: 1 pour continuer, 0 pour quitter
 */
int handle_command_execution(char *full_path, char **argv, char *program_name)
{
	pid_t pid;

	pid = create_process();
	if (pid == -1)
	{
		free(full_path);
		free_tokens(argv);
		return (1);
	}

	if (pid == 0)
	{
		/* Processus enfant : exécute la commande */
		execve(full_path, argv, environ);
		/* Si on arrive ici, execve a échoué */
		dprintf(STDERR_FILENO, "%s: %s: command not found\n", program_name, argv[0]);
		_exit(127);
	}
	else
	{
		/* Processus parent : attend l'enfant */
		wait_for_child(pid);
	}

	return (1);
}

/**
 * execute_command - Exécute une commande ou une commande intégrée
 * @command: La commande à exécuter
 * @program_name: Nom du programme shell
 * Return: 1 pour continuer, 0 pour quitter
 */
int execute_command(char *command, char *program_name)
{
	char **argv = NULL;
	char *full_path = NULL;
	int builtin_status;

	(void)program_name;

	/* Ignore les commandes vides */
	if (!command || is_empty_or_whitespace(command))
		return (1);

	/* Divise la commande en arguments */
	argv = _split_line(command);
	if (!argv || !argv[0])
	{
		free_tokens(argv);
		return (1);
	}

	/* Vérifie d'abord les commandes intégrées */
	builtin_status = check_builtin(argv);
	if (builtin_status == -1)
	{
		free_tokens(argv);
		return (0); /* Sort du shell */
	}
	else if (builtin_status == 1)
	{
		free_tokens(argv);
		return (1); /* Continue */
	}

	/* Cherche la commande dans le PATH */
	full_path = find_command(argv[0]);
	if (!full_path)
	{
		dprintf(STDERR_FILENO, "%s: %s: command not found\n", program_name, argv[0]);
		free_tokens(argv);
		return (1);
	}

	/* Exécute la commande */
	handle_command_execution(full_path, argv, program_name);

	/* Nettoie la mémoire */
	free(full_path);
	free_tokens(argv);
	return (1);
}
