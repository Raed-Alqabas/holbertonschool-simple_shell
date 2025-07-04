#include "shell.h"

/**
 * execute_command - Parses and executes a command line
 * @line: The input line to parse and execute
 * Return: Status code
 */
int execute_command(char *line)
{
	pid_t child_pid;
	int exit_status, arg_index = 0, env_index = 0;
	char *args[64], *token, *cmd_path;

	token = strtok(line, " \t\n");
	if (token == NULL)
		return (0);

	while (token != NULL && arg_index < 63)
	{
		args[arg_index++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[arg_index] = NULL;

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	if (strcmp(args[0], "env") == 0)
	{
		while (environ[env_index])
		{
			write(STDOUT_FILENO, environ[env_index], strlen(environ[env_index]));
			write(STDOUT_FILENO, "\n", 1);
			env_index++;
		}
		return (0);
	}

	if (strchr(args[0], '/'))
		cmd_path = args[0];
	else
	{
		cmd_path = find_path(args[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			return (127);
		}
	}

	if (access(cmd_path, X_OK) != 0)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		if (cmd_path != args[0])
			free(cmd_path);
		return (127);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		if (cmd_path != args[0])
			free(cmd_path);
		return (1);
	}

	if (child_pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			exit(127);
		}
	}
	else
	{
		wait(&exit_status);
		if (cmd_path != args[0])
			free(cmd_path);

		if (WIFEXITED(exit_status))
			return (WEXITSTATUS(exit_status));
		else
			return (1);
	}

	return (0);
}
