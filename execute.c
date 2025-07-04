#include "shell.h"

/**
 * execute - Executes only the ls command (as /bin/ls)
 * @args: array of command and arguments
 * @argv: program name (argv[0])
 * @cmd_count: command number (used in error messages)
 * Return: 1 to continue shell loop
 */
int execute(char **args, char *argv, __attribute__((unused)) int cmd_count)
{
	pid_t pid;
	int status;
	char *ls_path = "/bin/ls";

	if (!args[0])
		return (1);

	/* Replace "ls" with "/bin/ls" to execute it correctly */
	if (strcmp(args[0], "ls") == 0)
		args[0] = ls_path;

	/* Allow only /bin/ls */
	if (strcmp(args[0], ls_path) != 0)
	{
		fprintf(stderr, "%s: No such file or directory\n", argv);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror(argv);
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
