#include "shell.h"



/**
 * handle_builtin_env - Gère la commande intégrée env
 * @argv: Tableau d'arguments
 * Return: 1 pour continuer
 */
int handle_builtin_env(char **argv)
{
	int i;
	(void)argv; /* Éviter l'avertissement de paramètre non utilisé */

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (1); /* Continue le shell */
}

/**
 * execute_external_command - Exécute une commande externe
 * @argv: Tableau d'arguments
 * @full_path: Chemin complet de la commande
 * @program_name: Nom du programme
 * Return: 1 pour continuer
 */
int execute_external_command(char **argv, char *full_path, char *program_name)
{
	pid_t pid;
	int status;

	/* Création et exécution du processus - SEULEMENT si la commande existe */
	pid = fork();
	if (pid == 0)
	{
		/* Processus enfant */
		if (execve(full_path, argv, environ) == -1)
		{
			/* Erreur système - simple */
			perror(program_name);
			_exit(127); /* Code simple pour erreur */
		}
	}
	else if (pid < 0)
	{
		/* Échec du fork */
		perror("Error");
		return (1); /* Continue le shell */
	}
	else
	{
		/* Le processus parent attend l'enfant */
		wait(&status);
	}

	return (1); /* Continue le shell */
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
	int status = 1;

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
		status = handle_builtin_env(argv);
		free_tokens(argv);
		return (status);
	}

	/* Recherche du chemin complet de la commande */
	full_path = find_command(argv[0]);
	if (full_path == NULL)
	{
		/* Commande non trouvée - PAS de fork si la commande n'existe pas */
		fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_num, argv[0]);
		free_tokens(argv);
		return (1); /* Continue le shell */
	}

	/* Exécution de la commande externe */
	status = execute_external_command(argv, full_path, program_name);

	/* Nettoyage et continuation */
	free_tokens(argv);
	free(full_path);
	return (status);
}
