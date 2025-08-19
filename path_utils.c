#include "shell.h"

/**
 * file_exists - Vérifie si un fichier existe et est exécutable
 * @filepath: Chemin vers le fichier
 * Return: 1 si le fichier existe et est exécutable, 0 sinon
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
 * get_path_env - Récupère la variable d'environnement PATH
 * Return: Chaîne PATH ou NULL si non trouvée
 */
char *get_path_env(void)
{
	return (getenv("PATH"));
}

/**
 * find_command - Trouve le chemin complet d'une commande
 * @command: La commande à trouver
 * Return: Chemin complet si trouvé, NULL sinon
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
	if (!path_env)
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
