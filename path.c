#include "shell.h"
#include <string.h>

/**
 * get_env - get environment variable value
 * @name: variable name
 *
 * Return: pointer to value or NULL
 */
static char *get_env(const char *name)
{
	int i;
	size_t len = strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 &&
		    environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * join_path - build full path "dir/cmd"
 * @dir: directory
 * @cmd: command
 *
 * Return: allocated full path or NULL
 */
static char *join_path(const char *dir, const char *cmd)
{
	char *full;
	size_t a = strlen(dir), b = strlen(cmd);

	full = malloc(a + b + 2);
	if (full == NULL)
		return (NULL);

	memcpy(full, dir, a);
	full[a] = '/';
	memcpy(full + a + 1, cmd, b);
	full[a + b + 1] = '\0';

	return (full);
}

/**
 * resolve_cmd - resolve command using PATH
 * @cmd: command name
 * @av0: program name
 * @count: command number
 * @err_status: exit status on error
 *
 * Return: allocated full path or NULL
 */
char *resolve_cmd(char *cmd, char *av0, unsigned int count, int *err_status)
{
	char *path_env, *path_copy, *dir, *full;

	*err_status = 0;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);

	/* command contains '/' → no PATH */
	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));

		if (access(cmd, F_OK) == 0)
		{
			print_perm_denied(av0, count, cmd);
			*err_status = 126;
		}
		else
		{
			print_not_found(av0, count, cmd);
			*err_status = 127;
		}
		return (NULL);
	}

	path_env = get_env("PATH");
	if (path_env == NULL)
	{
		print_not_found(av0, count, cmd);
		*err_status = 127;
		return (NULL);
	}

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full = join_path(dir, cmd);
		if (full && access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	print_not_found(av0, count, cmd);
	*err_status = 127;
	return (NULL);
}
