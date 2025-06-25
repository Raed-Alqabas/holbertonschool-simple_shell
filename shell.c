#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/**
 *
 */
#define default_time_limit
pid_t child_pid;
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
		printf("my shell> ");
		if (!fgets(command, sizeof(command)), stdin)
		{
			break;
		}
		if (!strcmp(command,"qite\n"))
		{
			break;
		}
		execute(command, Time_limit);
	}
	return (0);
}

void execute(char *command, int Time_limit)
{
	char *args[100];
	int arg_count = 0, status;
	int time_Limit = default_time_limit;

	if (arg_count == 0)
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
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGALRM, handle_alarm);
		alarm(time_Limit);
		waitpid(child_pid, &status, 0);
		alarm(0);
		if (WIFEXITED(status))
		{
			printf("Child process exited with status %d\n", WEXITSTATUS);
		} elseif (WIFEXITED(status))
		{
			printf("Child process terminated by signal %d\n,", WTERMSTATUS);
		}
}

void handle_alarm(int sig)
{
	if (child_pid > 0)
	{
		kill(child_pid, SIGKILL);
		printf("Child process timed out and was terminated\n");
	}
}
