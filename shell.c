#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define default_time_limit 5
void execute(char *command, int Time_limit);
ssize_t read_line(char *buf, size_t size);
extern char **environ;
/**
 * get_child_pid - Accessor for child PID (used by signal handler)
 * @pid: Set a new child PID if not -1
 *
 * Return: The current child PID
 */
pid_t get_child_pid(pid_t pid)
{
	static pid_t child_pid = -1;

	if (pid != -1)
	{
		child_pid = pid;
	}
	return (child_pid);
}

/**
 * main - Entry point of the custom shell program
 * @argc: Argument count
 * @argv: Argument vector (optional time limit as first argument)
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int Time_limit = default_time_limit;
	char command[1024];

	if (argc == 2)
	{
		Time_limit = atoi(argv[1]);
	}
	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		if (!read_line(command, sizeof(command)))
		{
			break;
		}
		command[strcspn(command, "\n")] = '\0';
		if (!strcmp(command, "quit"))
		{
			break;
		}
		if (strcmp(command, "/bin/ls") != 0)
		{
			printf("./shell: No such file or directory\n");
			continue;
		}
		execute(command, Time_limit);
	}
	return (0);
}

/**
 * read_line - Reads a line from stdin using read()
 * @buf: Buffer to store input
 * @size: Size of the buffer
 *
 * Return: Number of bytes read, or -1 on failure
 */
ssize_t read_line(char *buf, size_t size)
{
	ssize_t n = read(STDIN_FILENO, buf, size -1);
	char *newline;

	if (n > 0)
	{
		buf[n] = '\0';
		newline = strchr(buf, '\n');
		if (newline)
			*newline = '\0';

	}

	return (n);
}

/**
 * execute - Forks and executes a single-word command with a timeout
 * @command: The command to execute (e.g. "ls", "date")
 * @Time_limit: Time limit in seconds before killing the child process
 *
 * Return: void
 */
void execute(char *command, int Time_limit)
{
	int status;
	pid_t child_pid;
	time_t start;

	start = time(NULL);
	command[strcspn(command, "\n")] = '\0';

	if (strlen(command) == 0)
	{
		return;
	}

	child_pid = fork();

	if (child_pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		char *args[2];

		args[0] = command;
		args[1] = NULL;
		execve(command, args, environ);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (1)
		{
			pid_t result = waitpid(child_pid, &status, WNOHANG);
			if (result == -1)
			{
				perror("waitpid");
				break;
			}
			else if (result == 0)
			{
				if (time(NULL) - start >= Time_limit)
				{
					kill(child_pid, SIGKILL);
					printf("Child process timed out and was terminated\n");
					break;
				}

			}
			else
				break;

		}
	}
}
