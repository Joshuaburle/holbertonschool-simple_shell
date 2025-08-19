#include "shell.h"
#include <errno.h>

/**
 * execute_command - Exécute une commande
 * @command: La commande à exécuter
 * @program_name: Nom du programme shell (argv[0])
 * Return: 1 pour continuer, 0 pour quitter
 */
int execute_command(char *command, char *program_name)
{
	pid_t pid;
	int status;
	char **argv;
	char *full_path;

	(void)program_name; /* Éviter l'avertissement de paramètre non utilisé */

	/* Gestion des commandes vides ou avec seulement des espaces */
	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

	/* Division de la commande en arguments */
	argv = _split_line(command);
	if (argv == NULL || argv[0] == NULL)
		return (1);

	/* Gestion de la commande intégrée exit */
	if (strcmp(argv[0], "exit") == 0)
	{
		free_tokens(argv);
		return (0);  /* Quitte le shell - PAS d'arguments */
	}

	/* Gestion de la commande intégrée env */
	if (strcmp(argv[0], "env") == 0)
	{
		int i;
		for (i = 0; environ[i] != NULL; i++)
		{
			printf("%s\n", environ[i]);
		}
		free_tokens(argv);
		return (1); /* Continue le shell */
	}

	/* Recherche du chemin complet de la commande */
	full_path = find_command(argv[0]);
	if (full_path == NULL)
	{
		/* Commande non trouvée */
		dprintf(STDERR_FILENO, "%s: 1: %s: not found\n", program_name, argv[0]);
		free_tokens(argv);
		return (1); /* Continue le shell */
	}



	/* Création et exécution du processus */
	pid = fork();
	if (pid == 0)
	{
		/* Processus enfant */
		if (execve(full_path, argv, environ) == -1)
		{
			/* Erreur système - simple */
			perror(program_name);
			free_tokens(argv);
			free(full_path);
			_exit(127); /* Code simple pour erreur */
		}
	}
	else if (pid < 0)
	{
		/* Échec du fork */
		perror("Error");
		free_tokens(argv);
		free(full_path);
		return (1); /* Continue le shell */
	}
	else
	{
		/* Le processus parent attend l'enfant */
		wait(&status);
	}

	/* Nettoyage et continuation */
	free_tokens(argv);
	free(full_path);
	return (1); /* Continue le shell */
}
