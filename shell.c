#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "shell.h"

/**
 * shell_loop - Boucle principale du shell
 * @env: Variables d'environnement
 */
void shell_loop(char **env)
{
	char *input;
	char **args;
	shell_info_t info;
	int status = 1;

	info.env = env;
	info.exit_status = 0;

	while (status)
	{
		/* Affichage du prompt */
		if (isatty(STDIN_FILENO))
			printf("%s", PROMPT);

		/* Lecture de l'entrée utilisateur */
		input = read_input();
		if (input == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		/* Parsing de l'entrée */
		args = parse_input(input);
		if (args != NULL && args[0] != NULL)
		{
			/* Exécution de la commande */
			status = execute_command(args, env, "./shell");
		}

		/* Libération de la mémoire */
		free(input);
		free_args(args);
	}
}

/**
 * read_input - Lit l'entrée utilisateur
 * Return: Pointeur vers la chaîne lue ou NULL en cas d'erreur
 */
char *read_input(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read_chars;

	read_chars = getline(&input, &len, stdin);
	if (read_chars == -1)
	{
		free(input);
		return (NULL);
	}

	/* Suppression du caractère de nouvelle ligne */
	if (input[read_chars - 1] == '\n')
		input[read_chars - 1] = '\0';

	return (input);
}

/**
 * parse_input - Parse l'entrée utilisateur en arguments
 * @input: Chaîne d'entrée
 * Return: Tableau d'arguments ou NULL en cas d'erreur
 */
char **parse_input(char *input)
{
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *token;
	int i = 0;

	if (args == NULL)
		return (NULL);

	token = strtok(input, " \t");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i] = strdup(token);
		if (args[i] == NULL)
		{
			free_args(args);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	return (args);
}

/**
 * execute_command - Exécute une commande
 * @args: Tableau d'arguments
 * @env: Variables d'environnement
 * @program_name: Nomme du programme
 * Return: Statut de sortie
 */
int execute_command(char **args, char **env, char *program_name)
{
	pid_t pid;
	int status;

	if (args == NULL || args[0] == NULL)
		return (0);

	/* Pas de built-ins selon les exigences de la tâche */

	/* Création d'un nouveau processus */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		/* Processus enfant */
		if (execve(args[0], args, env) == -1)
		{
			print_error(program_name);
			exit(1);
		}
	}
	else
	{
		/* Processus parent */
		waitpid(pid, &status, 0);
	}

	return (WEXITSTATUS(status));
}

/**
 * print_error - Affiche un message d'erreur
 * @program_name: Nom du programme
 * @command: Commande qui a échoué
 */
void print_error(char *program_name)
{
	fprintf(stderr, "%s: No such file or directory\n", program_name);
}

/**
 * free_args - Libère la mémoire allouée pour les arguments
 * @args: Tableau d'arguments à libérer
 */
void free_args(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	free(args);
}
