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
 * find_command - Trouve le chemin complet d'une commande dans le PATH
 * @cmd: La commande à trouver
 * Return: Chemin complet si trouvé, NULL sinon
 */
char *find_command(const char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;

	/* Si c'est un chemin absolu, le retourne directement */
	if ((cmd[0] == '/') || ((cmd[0] == '.') && (cmd[1] == '/')))
	{
		return (strdup(cmd));
	}

	/* Récupère la variable PATH */
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	/* Cherche dans chaque répertoire du PATH */
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		/* Construit le chemin complet */
		sprintf(full_path, "%s/%s", dir, cmd);

		/* Vérifie si le fichier existe et est exécutable */
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
