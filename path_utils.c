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
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
}

/**
 * find_command - Trouve et exécute une commande
 * @args: Arguments de la commande
 * @program_name: Nom du programme shell
 * Return: 0 en cas de succès, 127 en cas d'échec
 */
int find_command(char **args, char *program_name)
{
	char *full_path;

	/* Gestion des commandes vides */
	if (args == NULL || args[0] == NULL)
		return (127);

	/* Gestion des commandes intégrées */
	if (strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, program_name));

	if (strcmp(args[0], "env") == 0)
		return (builtin_env(args, program_name));

	/* Gestion des chemins absolus */
	if (strchr(args[0], '/') != NULL)
	{
		if (file_exists(args[0]))
			return (execute_command(args[0], args, program_name));
		
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		return (127);
	}

	/* Recherche dans le PATH */
	full_path = find_command_in_path(args[0]);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		return (127);
	}

	/* Exécution de la commande trouvée */
	return (execute_command(full_path, args, program_name));
}

/**
 * find_command_in_path - Trouve une commande dans le PATH
 * @command: Nom de la commande
 * Return: Chemin complet ou NULL si non trouvé
 */
char *find_command_in_path(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t needed_size;

	/* Récupération de la variable d'environnement PATH */
	path_env = get_path_env();
	if (!path_env || strlen(path_env) == 0)
		return (NULL);

	/* Recherche dans les répertoires du PATH */
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
