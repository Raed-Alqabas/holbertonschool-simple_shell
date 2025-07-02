#include "shell.h"

/**
 * read_line - Reads a line of input from stdin
 * Return: Pointer to the line read
 */
char *read_line(void)
{
	char *input_line = NULL;
	size_t input_size = 0;

	if (getline(&input_line, &input_size, stdin) == -1)
	{
		free(input_line);
		return (NULL);
	}
	return (input_line);
}

/**
 * split_line - Splits a line into tokens (arguments)
 * @line: The input string to tokenize
 * Return: Array of strings (tokens)
 */
char **split_line(char *line)
{
	int token_capacity = 64, token_index = 0;
	char **token_array = malloc(token_capacity * sizeof(char *));
	char *current_token;

	if (!token_array)
		exit(EXIT_FAILURE);

	current_token = strtok(line, " \t\r\n");
	while (current_token)
	{
		token_array[token_index++] = strdup(current_token);
		if (token_index >= token_capacity)
		{
			token_capacity += 64;
			token_array = realloc(token_array, token_capacity * sizeof(char *));
			if (!token_array)
				exit(EXIT_FAILURE);
		}
		current_token = strtok(NULL, " \t\r\n");
	}
	token_array[token_index] = NULL;
	return (token_array);
}

/**
 * _getenv - Retrieves the value of an environment variable
 * @name: Name of the environment variable to search for
 * Return: Pointer to the value string or NULL if not found
 */
char *_getenv(const char *name)
{
	int env_index = 0;
	size_t name_length = strlen(name);

	while (environ[env_index])
	{
		if (strncmp(environ[env_index], name, name_length) == 0 &&
		    environ[env_index][name_length] == '=')
		{
			return (environ[env_index] + name_length + 1);
		}
		env_index++;
	}
	return (NULL);
}
