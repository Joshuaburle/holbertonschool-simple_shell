#include "shell.h"
#include <string.h>

/**
 * handle_exit - handle exit builtin
 * @argv: argument vector
 * @line: input line buffer
 * @last_status: last command exit status
 *
 * Return: 1 if shell should exit, 0 otherwise
 */
int handle_exit(char **argv, char *line, int last_status)
{
	if (argv[0] && strcmp(argv[0], "exit") == 0)
	{
		free_args(argv);
		free(line);
		exit(last_status);
	}
	return (0);
}

/**
 * process_line - parse and execute a single command line
 * @line: input line buffer
 * @av: argument vector
 * @count: command counter
 * @last_status: pointer to last status
 *
 * Return: 1 if shell should exit, 0 otherwise
 */
int process_line(char *line, char **av, unsigned int *count, int *last_status)
{
	char **argv_exec;
	char *cmd_path;

	argv_exec = parse_args(line);
	if (argv_exec == NULL)
		return (0);

	if (handle_exit(argv_exec, line, *last_status))
		return (1);

	(*count)++;
	cmd_path = resolve_cmd(argv_exec[0], av[0], *count, last_status);
	if (cmd_path != NULL)
	{
		argv_exec[0] = cmd_path;
		*last_status = execute_command(argv_exec, av[0], *count);
		free(cmd_path);
	}
	free_args(argv_exec);

	return (0);
}

/**
 * shell_loop - main shell loop
 * @av: argument vector
 *
 * Return: last command status
 */
int shell_loop(char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	unsigned int count = 0;
	int last_status = 0;
	int interactive;

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

		if (process_line(line, av, &count, &last_status))
			break;
	}

	free(line);
	return (last_status);
}

/**
 * main - entry point
 * @ac: argument count (unused)
 * @av: argument vector
 *
 * Return: exit status
 */
int main(int ac, char **av)
{
	int status;

	(void)ac;
	status = shell_loop(av);
	return (status);
}
