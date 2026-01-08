#include "shell.h"

/**
 * print_not_found - command not found error
 * @av0: program name
 * @count: command number
 * @cmd: command name
 */
void print_not_found(char *av0, unsigned int count, char *cmd)
{
	fprintf(stderr, "%s: %u: %s: not found\n", av0, count, cmd);
}

/**
 * print_perm_denied - permission denied error
 * @av0: program name
 * @count: command number
 * @cmd: command name
 */
void print_perm_denied(char *av0, unsigned int count, char *cmd)
{
	fprintf(stderr, "%s: %u: %s: Permission denied\n", av0, count, cmd);
}
