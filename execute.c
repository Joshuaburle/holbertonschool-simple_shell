#include "shell.h"

/* Crée un nouveau processus enfant */
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

/* Attend que le processus enfant se termine */
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

/* Exécute une commande ou une commande intégrée */
int execute_command(char *command, char *program_name)
{
	pid_t pid;
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
		dprintf(STDERR_FILENO, "./shell: No such file or directory\n");
		free_tokens(argv);
		return (1);
	}

	/* Crée le processus enfant */
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
		dprintf(STDERR_FILENO, "./shell: No such file or directory\n");
		_exit(2);
	}
	else
	{
		/* Processus parent : attend l'enfant */
		wait_for_child(pid);
	}

	/* Nettoie la mémoire */
	free(full_path);
	free_tokens(argv);
	return (1);
}
