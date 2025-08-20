#include "shell.h"

/**
 * display_prompt - Affiche le prompt du shell
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
	fflush(stdout);
}

/**
 * read_line - Lit une ligne depuis stdin
 * Return: Pointeur vers la ligne, ou NULL si EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_size;

	read_size = getline(&line, &len, stdin);
	if (read_size == -1)
	{
		free(line);
		return (NULL);
	}

	/* Supprimer le caractère de nouvelle ligne */
	if (read_size > 0 && line[read_size - 1] == '\n')
		line[read_size - 1] = '\0';

	return (line);
}

/**
 * split - Divise une ligne en un seul argument (pour la tâche 0.1)
 * @line: La ligne à analyser
 * Return: Tableau avec un seul argument, ou NULL en cas d'erreur
 */
char **split(char *line)
{
	char **args = malloc(2 * sizeof(char *));
	char *token;

	if (args == NULL)
		return (NULL);

	/* Prendre seulement le premier mot (pas d'arguments) */
	token = strtok(line, " \t\r\n");
	if (token == NULL)
	{
		free(args);
		return (NULL);
	}

	args[0] = token;
	args[1] = NULL;

	return (args);
}

/**
 * execute_command - Exécute une commande (un seul mot, pas d'arguments)
 * @command: La commande à exécuter
 * @program_name: Nom du programme pour les messages d'erreur
 * Return: 1 pour continuer la boucle, 0 pour quitter
 */
int execute_command(char *command, char *program_name)
{
	char **args;
	pid_t pid;
	int status;

	/* Diviser la ligne de commande en un seul argument */
	args = split(command);
	if (args == NULL)
		return (1);

	/* Vérifier si la commande est vide */
	if (args[0] == NULL)
	{
		free(args);
		return (1);
	}

	/* Créer un nouveau processus */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(args);
		return (1);
	}

	if (pid == 0)
	{
		/* Processus enfant - exécuter la commande */
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", program_name);
			free(args);
			exit(1);
		}
	}
	else
	{
		/* Processus parent - attendre la fin de l'enfant */
		waitpid(pid, &status, 0);
	}

	free(args);
	return (1);
}
