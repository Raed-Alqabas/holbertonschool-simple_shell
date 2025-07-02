#include "shell.h"

/**
 * execute - Executes only the /bin/ls command, rejects all others
 * @args: array of command and arguments
 * @argv: program name (argv[0])
 * @cmd_count: command number (used in error messages)
 * Return: 1 to continue shell loop
 */
int execute(char **args, char *argv, __attribute__((unused)) int cmd_count)
{
	pid_t pid;
	int status;

	if (!args[0])
		return (1);

	/* Reject anything that is not exactly "/bin/ls" */
	if (strcmp(args[0], "/bin/ls") != 0)
	{
		fprintf(stderr, "%s: No such file or directory\n",
		        argv);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror("execve"); /* Should only fail if /bin/ls is somehow broken */
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (1);
}
