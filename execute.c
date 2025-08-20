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
 * execute_command - Exécute une commande simple (Tâche 0.1)
 * @command: La commande à exécuter (un seul mot)
 * @program_name: Nom du programme shell
 * Return: 1 pour continuer, 0 pour quitter
 */
int execute_command(char *command, char *program_name)
{
	pid_t pid;
	char *full_path = NULL;

	(void)program_name;

	/* Ignore les commandes vides */
	if (!command || is_empty_or_whitespace(command))
		return (1);

	/* Vérifie si la commande existe et est exécutable */
	if (access(command, X_OK) == 0)
	{
		full_path = strdup(command);
	}
	else
	{
		/* Commande non trouvée */
		dprintf(STDERR_FILENO, "./shell: No such file or directory\n");
		return (1);
	}

	/* Crée le processus enfant */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		return (1);
	}

	if (pid == 0)
	{
		/* Processus enfant : exécute la commande */
		char *argv[] = {command, NULL};
		execve(full_path, argv, environ);
		/* Si on arrive ici, execve a échoué */
		dprintf(STDERR_FILENO, "./shell: No such file or directory\n");
		_exit(2);
	}
	else
	{
		/* Processus parent : attend l'enfant */
		wait(NULL);
	}

	/* Nettoie la mémoire */
	free(full_path);
	return (1);
}
