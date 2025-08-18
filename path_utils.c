#include "shell.h"
#include <sys/stat.h>

/**
 * get_path - Récupère le chemin d'environnement PATH
 * Return: chemin d'environnement PATH
 */
char *get_path(void)
{
	char *path_env, *path_copy;
	int i;

	/* Récupérer la variable d'environnement PATH */
	path_env = NULL;
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
	}
	if (path_env == NULL)
		return (NULL);

	/* Copier PATH pour éviter de modifier l'original */
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	return (path_copy);
}

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
		if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
			return (1);
	}

	return (0);
}

/**
 * exec_full_path - Construit le chemin complet et vérifie si l'exécutable existe
 * @command: La commande à trouver
 * @dir: Répertoire à vérifier
 * Return: Chemin complet si l'exécutable existe, NULL sinon
 */
char *exec_full_path(char *command, char *dir)
{
	char *full_path;

	full_path = malloc(strlen(dir) + strlen(command) + 2);
	if (full_path == NULL)
		return (NULL);

	sprintf(full_path, "%s/%s", dir, command);

	if (file_exists(full_path))
		return (full_path);

	free(full_path);
	return (NULL);
}

/**
 * find_path - Trouve le chemin complet d'une commande
 * @command: La commande à trouver
 * Return: Chemin complet vers la commande, ou NULL si non trouvée
 */
char *find_path(char *command)
{
	char *path_copy, *dir, *full_path;

	/* Vérifier si la commande est NULL ou vide */
	if (!command || strlen(command) == 0)
		return (NULL);

	/* Si la commande contient '/', vérifier si elle existe */
	if (strchr(command, '/') != NULL)
	{
		if (file_exists(command))
			return (strdup(command));
		return (NULL);
	}

	path_copy = get_path();
	if (path_copy == NULL)
		return (NULL);

	/* Rechercher dans chaque répertoire du PATH */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		/* Ignorer les entrées de répertoire vides */
		if (strlen(dir) > 0)
		{
			full_path = exec_full_path(command, dir);
			if (full_path != NULL)
			{
				free(path_copy);
				return (full_path);
			}
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
