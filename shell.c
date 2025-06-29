#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define default_time_limit 5
void execute(char *command, int Time_limit);
void handle_alarm(int sig);
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
		printf("#cisfun$ ");
		if (!fgets(command, sizeof(command), stdin))
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
		char *args[] = {"/bin/ls", NULL};

		execve("/bin/ls", args, environ);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		get_child_pid(child_pid);
		signal(SIGALRM, handle_alarm);
		alarm(Time_limit);
		waitpid(child_pid, &status, 0);
		alarm(0);
	}
}

/**
 * handle_alarm - Signal handler for SIGALRM
 * @sig: The signal number (unused)
 *
 * Description: Called when the alarm times out; kills the child process
 * Return: void
 */
void handle_alarm(int sig __attribute__((unused)))
{
	pid_t child_pid = get_child_pid(-1);

	if (child_pid > 0)
	{
		kill(child_pid, SIGKILL);
		printf("Child process timed out and was terminated\n");
	}
}
