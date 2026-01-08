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
 * execute_command - creates a process and executes a command
 * @cmd: command to execute
 * @av0: program name
 * @count: command number
 */
void execute_command(char *cmd, char *av0, unsigned int count)
{
	pid_t pid;
	int status;
	char *argv_exec[2];

	argv_exec[0] = cmd;
	argv_exec[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, argv_exec, environ);

		if (errno == ENOENT)
			print_not_found(av0, count, cmd);
		else
			perror(av0);

		_exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * main - Simple UNIX command line interpreter (task 0.1)
 * @ac: argument count (unused)
 * @av: argument vector
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	char *line = NULL, *cmd = NULL;
	size_t len = 0;
	ssize_t nread;
	unsigned int count = 0;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		cmd = strtok(line, " \t\n");
		if (cmd == NULL)
			continue;

		count++;
		execute_command(cmd, av[0], count);
	}

	free(line);
	return (0);
}
