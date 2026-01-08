#include "shell.h"
#include <errno.h>

/**
 * child_exec - execute command in child
 * @argv: argument vector
 * @av0: program name
 * @count: command number
 */
static void child_exec(char **argv, char *av0, unsigned int count)
{
	execve(argv[0], argv, environ);

	if (errno == ENOENT)
	{
		print_not_found(av0, count, argv[0]);
		_exit(127);
	}
	if (errno == EACCES)
	{
		print_perm_denied(av0, count, argv[0]);
		_exit(126);
	}

	perror(av0);
	_exit(1);
}

/**
 * execute_command - fork and execute argv
 * @argv: argument vector
 * @av0: program name
 * @count: command number
 *
 * Return: exit status
 */
int execute_command(char **argv, char *av0, unsigned int count)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(av0);
		return (1);
	}

	if (pid == 0)
		child_exec(argv, av0, count);

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
