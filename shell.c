#include "shell.h"

/**
 * main - The entry point of the shell.
 *
 * Return: Exit status
 */
int main(void)
{
	char *input_line;
	int exit_status = 0;
	int is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_interactive)
			display_prompt();

		input_line = read_input();
		if (input_line == NULL)
		{
			if (is_interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (input_line[0] != '\0')
		{
			if (strncmp(input_line, "exit", 4) == 0 &&
			    (input_line[4] == '\n' || input_line[4] == '\0' || input_line[4] == ' '))
			{
				free(input_line);
				break;
			}
			exit_status = execute_command(input_line);
		}
		free(input_line);
	}
	return (exit_status);
}
