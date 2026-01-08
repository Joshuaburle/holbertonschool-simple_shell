#include "shell.h"
#include <string.h>
#include <errno.h>

/**
 * print_not_found - prints error message like /bin/sh
 * @av0: program name
 * @count: command number
 * @cmd: command name
 */
void print_not_found(char *av0, unsigned int count, char *cmd)
{
	fprintf(stderr, "%s: %u: %s: not found\n", av0, count, cmd);
}

/**
 * print_perm_denied - prints permission denied like /bin/sh
 * @av0: program name
 * @count: command number
 * @cmd: command name
 */
void print_perm_denied(char *av0, unsigned int count, char *cmd)
{
	fprintf(stderr, "%s: %u: %s: Permission denied\n", av0, count, cmd);
}

/**
 * child_exec - executes command in child process
 * @cmd: command to execute
 * @av0: program name
 * @count: command number
 */
void child_exec(char *cmd, char *av0, unsigned int count)
{
	char *argv_exec[2];

	argv_exec[0] = cmd;
	argv_exec[1] = NULL;

	execve(cmd, argv_exec, environ);

	if (errno == ENOENT)
	{
		print_not_found(av0, count, cmd);
		_exit(127);
	}
	if (errno == EACCES)
	{
		print_perm_denied(av0, count, cmd);
		_exit(126);
	}

	perror(av0);
	_exit(1);
}

/**
 * execute_command - creates a process and executes a command
 * @cmd: command to execute
 * @av0: program name
 * @count: command number
 *
 * Return: exit status of the executed command
 */
int execute_command(char *cmd, char *av0, unsigned int count)
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
		child_exec(cmd, av0, count);

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}

/**
 * main - Simple UNIX command line interpreter (task 0.1)
 * @ac: argument count (unused)
 * @av: argument vector
 *
 * Return: exit status of the last executed command
 */
int main(int ac, char **av)
{
	char *line = NULL, *cmd = NULL;
	size_t len = 0;
	ssize_t nread;
	unsigned int count = 0;
	int last_status = 0;
	int interactive;

	(void)ac;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		cmd = strtok(line, " \t\n");
		if (cmd == NULL)
			continue;

		count++;
		last_status = execute_command(cmd, av[0], count);
	}

	free(line);
	return (last_status);
}
