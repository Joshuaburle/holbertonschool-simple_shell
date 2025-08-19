#include "shell.h"

/**
 * execute_command - Exécute une commande externe
 * @full_path: Chemin complet de la commande
 * @argv: Arguments de la commande
 * @program_name: Nom du programme shell
 * Return: 0 en cas de succès, 127 en cas d'échec
 */
int execute_command(char *full_path, char **argv, char *program_name)
{
	pid_t pid;
	int status;

	/* Création et exécution du processus */
	pid = fork();
	if (pid == 0)
	{
		/* Processus enfant */
		if (execve(full_path, argv, environ) == -1)
		{
			perror(program_name);
			_exit(127);
		}
	}
	else if (pid < 0)
	{
		/* Échec du fork */
		perror("Error");
		return (127);
	}
	else
	{
		/* Le processus parent attend l'enfant */
		wait(&status);
	}

	return (0);
}
