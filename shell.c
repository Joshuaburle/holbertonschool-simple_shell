#include "shell.h"

/**
 * main - Simple UNIX command line interpreter
 * @ac: Argument count (unused)
 * @av: Argument vector
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0')
			continue;

		pid = fork();
		if (pid == 0)
		{
			char *argv_exec[2];

			argv_exec[0] = line;
			argv_exec[1] = NULL;

			execve(line, argv_exec, environ);
			perror(av[0]);
			_exit(127);
		}
		waitpid(pid, &status, 0);
	}

	free(line);
	return (0);
}
