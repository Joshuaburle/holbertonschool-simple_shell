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
 * get_path_env - Get PATH environment variable
 * Return: PATH string or NULL if not found
 */
char *get_path_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
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

	/* Handle absolute paths */
	if (strchr(command, '/') != NULL)
		return (file_exists(command) ? strdup(command) : NULL);

	/* Get PATH environment */
	path_env = get_path_env();
	if (!path_env || strlen(path_env) == 0)
		return (NULL);

	/* Search in PATH directories */
	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		needed_size = strlen(dir) + 1 + strlen(command) + 1;
		full_path = malloc(needed_size);
		if (full_path)
		{
			snprintf(full_path, needed_size, "%s/%s", dir, command);
			if (file_exists(full_path))
			{
				free(path_copy);
				return (full_path);
			}
			free(full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
