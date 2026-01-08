#include "shell.h"

/**
 * main - Simple shell 0.3 (arguments + PATH)
 * @ac: argument count (unused)
 * @av: argument vector
 *
 * Return: exit status of last command
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	unsigned int count = 0;
	int last_status = 0;
	int interactive;
	char **argv_exec;
	char *cmd_path;

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

		argv_exec = parse_args(line);
		if (argv_exec == NULL)
			continue;

		count++;

		cmd_path = resolve_cmd(argv_exec[0], av[0], count, &last_status);
		if (cmd_path == NULL)
		{
			free_args(argv_exec);
			continue;
		}

		argv_exec[0] = cmd_path;
		last_status = execute_command(argv_exec, av[0], count);

		free(cmd_path);
		free_args(argv_exec);
	}

	free(line);
	return (last_status);
}
