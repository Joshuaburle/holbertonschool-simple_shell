#include "shell.h"

/**
 * find_command - trouve le chemin complet d'une commande
 * @cmd: nom de la commande
 * 
 * Règles projet 0.2 : pas de PATH, seulement chemins absolus/relatifs
 * Return: chemin complet si trouvé, NULL sinon
 */
char *find_command(const char *cmd)
{
	/* Si c'est un chemin absolu ou relatif, le retourner directement */
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		return strdup(cmd);
	}
	
	/* Sinon, essayer avec ./ devant (chemin relatif) */
	char *relative_path = malloc(strlen(cmd) + 3);
	if (!relative_path)
		return NULL;
	
	sprintf(relative_path, "./%s", cmd);
	return relative_path;
}
