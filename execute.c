#include "shell.h"

/**
 * write_error - Écrit un message d'erreur sur stderr
 * @prog: Nom du programme
 * @cmd: Commande qui a échoué
 * @msg: Message d'erreur
 */
void write_error(char *prog, char *cmd, char *msg)
{
	fprintf(stderr, "%s: 1: %s: %s\n", prog, cmd, msg);
}

/**
 * handle_builtin - Handle built-in commands
 * @argv: Command arguments
 * @command_copy: Copy of original command
 * Return: 0 if builtin was handled and succeeded, -1 if not a builtin
 */
int handle_builtin(char **argv, char *command_copy)
{
	int exit_code = g_last_exit_code; /* Use last exit code as default */
	
	/* Check if it's an exit command */
	if (strcmp(argv[0], "exit") == 0)
	{
		/* Parse exit code if provided */
		if (argv[1] != NULL)
		{
			exit_code = atoi(argv[1]);
		}
		free_tokens(argv);
		free(command_copy);
		exit(exit_code); /* Exit directly - never returns */
	}

	/* Check if it's env command */
	if (strcmp(argv[0], "env") == 0)
	{
		print_env();
		free_tokens(argv);
		free(command_copy);
		return (0); /* Success */
	}

	return (-1); /* Not a builtin */
}

/**
 * handle_command_not_found - Gère les erreurs de commandes non trouvées
 * @program_name: Nom du programme
 * @argv: Arguments
 * @command_copy: Copie de la commande
 * Return: Code d'erreur approprié
 */
int handle_command_not_found(char *program_name, char **argv, char *command_copy)
{
	/* Check if it's an absolute path with permission issue */
	if ((argv[0][0] == '/') || ((argv[0][0] == '.') && (argv[0][1] == '/')))
	{
		/* It's an absolute path - check if file exists but not executable */
		struct stat st;

		if (stat(argv[0], &st) == 0)
		{
			write_error(program_name, argv[0], "Permission denied");
			free_tokens(argv);
			free(command_copy);
			return (126);
		}
		else
		{
			write_error(program_name, argv[0], "No such file or directory");
			free_tokens(argv);
			free(command_copy);
			return (127);
		}
	}
	/* Command not found - print error and don't fork */
	write_error(program_name, argv[0], "command not found");
	free_tokens(argv);
	free(command_copy);
	return (127);
}

/**
 * execute_fork - Execute command in child process
 * @cmd_path: Path to command
 * @argv: Array of arguments
 * @command_copy: Copy of original command
 * Return: Code de sortie
 */
int execute_fork(char *cmd_path, char **argv, char *command_copy)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(cmd_path, argv, environ) == -1)
		{
			perror(argv[0]);
			free_tokens(argv);
			free(cmd_path);
			free(command_copy);
			_exit(127);
		}
		/* execve succeeded, this should never be reached */
		_exit(0);
	}
	else if (pid < 0)
	{
		/* Fork failed */
		write(STDERR_FILENO, "Error: fork failed\n", 19);
		free_tokens(argv);
		free(cmd_path);
		free(command_copy);
		return (1);
	}
	else
	{
		/* Parent process waits for child */
		wait(&status);

		/* Free allocated memory */
		free_tokens(argv);
		free(cmd_path);
		free(command_copy);

		/* Return the exit status of the child */
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
}

/**
 * execute_command - Executes a command
 * @command: The command to execute
 * @program_name: Name of the shell program (argv[0])
 * Return: 1 to continue, 0 to exit
 */
int execute_command(char *command, char *program_name)
{
	char **argv;
	char *cmd_path;
	char *command_copy;

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

	/* Make a copy of the command before tokenizing */
	command_copy = strdup(command);
	if (!command_copy)
		return (1);

	/* Split command into arguments */
	argv = _split_line(command_copy);
	if (argv == NULL || argv[0] == NULL)
	{
		if (argv)
			free_tokens(argv);
		free(command_copy);
		return (1);
	}

	/* Handle built-in commands like exit and env */
	if (handle_builtin(argv, command_copy) != -1)
		return (0); /* Builtin was handled successfully */

	/* For Simple shell 0.3+ - Handle PATH, don't fork if command doesn't exist */
	cmd_path = find_command(argv[0]);
	if (cmd_path == NULL)
	{
		/* Command not found - handle error appropriately */
		return (handle_command_not_found(program_name, argv, command_copy));
	}

	/* Execute the command using the new execute_fork function */
	return (execute_fork(cmd_path, argv, command_copy));
}


