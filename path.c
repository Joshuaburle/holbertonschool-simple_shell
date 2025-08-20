#include "shell.h"

/**
 * _getenv - Recherche une variable d'environnement
 * @name: Nom de la variable à rechercher
 * Return: Valeur de la variable ou NULL si non trouvée
 */
char *_getenv(const char *name)
{
	int i, name_len;

	if (!name || !environ)
		return (NULL);

	name_len = strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && 
		    environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
	}
	return (NULL);
}

/**
 * build_full_path - Construit le chemin complet vers une commande
 * @directory: Répertoire de base
 * @command: Nom de la commande
 * Return: Chemin complet alloué ou NULL en cas d'erreur
 */
static char *build_full_path(const char *directory, const char *command)
{
	char *path;
	int dir_len, cmd_len;

	if (!directory || !command)
		return (NULL);

	dir_len = strlen(directory);
	cmd_len = strlen(command);
	
	path = malloc(dir_len + cmd_len + 2);
	if (!path)
		return (NULL);

	strcpy(path, directory);
	if (directory[dir_len - 1] != '/')
		strcat(path, "/");
	strcat(path, command);

	return (path);
}

/**
 * find_command - Localise une commande dans le PATH
 * @cmd: Nom de la commande à localiser
 * Return: Chemin complet vers la commande ou NULL si non trouvée
 */
char *find_command(const char *cmd)
{
	char *path_env, *path_dup, *current_dir, *full_path;

	if (!cmd)
		return (NULL);

	/* Si la commande contient un slash, c'est un chemin */
	if (strchr(cmd, '/') != NULL)
		return (strdup(cmd));

	/* Récupération de la variable PATH */
	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	/* Duplication pour manipulation avec strtok */
	path_dup = strdup(path_env);
	if (!path_dup)
		return (NULL);

	/* Parcours de chaque répertoire du PATH */
	current_dir = strtok(path_dup, ":");
	while (current_dir != NULL)
	{
		full_path = build_full_path(current_dir, cmd);
		if (full_path)
		{
			if (access(full_path, X_OK) == 0)
			{
				free(path_dup);
				return (full_path);
			}
			free(full_path);
		}
		current_dir = strtok(NULL, ":");
	}

	free(path_dup);
	return (NULL);
}
