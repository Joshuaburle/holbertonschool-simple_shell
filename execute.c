#include "shell.h"

/**
 * file_exists - Checks if a file exists and is executable
 * @filepath: Path to the file
 * Return: 1 if file exists and is executable, 0 otherwise
 */
int file_exists(char *filepath)
{
	struct stat st;

	if (stat(filepath, &st) == 0)
	{
		if (S_ISREG(st.st_mode) && access(filepath, X_OK) == 0)
			return (1);
	}

	return (0);
}

/**
 * free_tokens - Frees memory allocated for tokens array
 * @tokens: Array of tokens to free
 */
void free_tokens(char **tokens)
{
	if (tokens == NULL)
		return;

	/* Note: We don't free individual tokens because they point to parts of the original line */
	free(tokens);
}

/**
 * find_command - Finds the full path of a command
 * @command: The command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_command(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t needed_size;
	int i;

	/* 1. Si la commande contient déjà un '/' */
	if (strchr(command, '/') != NULL)
	{
		if (file_exists(command))
			return (strdup(command));
		return (NULL);
	}

	/* 2. Récupérer le PATH depuis environ (plus robuste) */
	path_env = NULL;
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
	}

	if (!path_env || strlen(path_env) == 0)
		return (NULL);

	/* 3. Faire une copie modifiable */
	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	/* 4. Parcourir chaque dossier du PATH */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		/* 5. Construire le chemin complet avec taille dynamique */
		needed_size = strlen(dir) + 1 + strlen(command) + 1;
		full_path = malloc(needed_size);
		if (!full_path)
		{
			dir = strtok(NULL, ":");
			continue;
		}

		snprintf(full_path, needed_size, "%s/%s", dir, command);

		/* 6. Vérifier si le fichier existe et est exécutable */
		if (file_exists(full_path))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	/* 7. Rien trouvé */
	free(path_copy);
	return (NULL);
}

/**
 * _split_line - Splits a string into an array of tokens
 * @line: The string to split
 * Return: Array of tokens, or NULL on failure
 */
char **_split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		/* Retourner NULL au lieu de fermer le shell */
		return (NULL);
	}

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				/* Retourner NULL au lieu de fermer le shell */
				return (NULL);
			}
		}

		token = strtok(NULL, " \t\r\n");
	}

	tokens[position] = NULL;
	return (tokens);
}

/**
 * execute_command - Executes a command
 * @command: The command to execute
 * @program_name: Name of the shell program (argv[0])
 * Return: 1 to continue, 0 to exit
 */
int execute_command(char *command, char *program_name)
{
	pid_t pid;
	int status;
	char **argv;
	char *full_path;

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

	/* Split command into arguments */
	argv = _split_line(command);
	if (argv == NULL)
		return (1);

	/* Check if it's an exit command */
	if (strcmp(argv[0], "exit") == 0)
	{
		free_tokens(argv);
		return (0);
	}

	/* Find the full path of the command BEFORE forking */
	full_path = find_command(argv[0]);
	if (full_path == NULL)
	{
		/* Command not found - don't fork, just show error */
		fprintf(stderr, "%s: %s: command not found\n", program_name, argv[0]);
		free_tokens(argv);
		return (1);
	}

	/* Now we know the command exists, so we can fork */
	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(full_path, argv, environ) == -1)
		{
			perror(program_name);
			free_tokens(argv);
			free(full_path);
			_exit(127);
		}
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("Error");
		free_tokens(argv);
		free(full_path);
		return (1);
	}
	else
	{
		/* Parent process waits for child */
		wait(&status);
	}

	/* Free allocated memory */
	free_tokens(argv);
	free(full_path);
	return (1);
}
