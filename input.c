#include "shell.h"

/**
 * is_whitespace - Checks if the char is a "whitespace" character.
 * @c: The character to check
 *
 * Return: 1 if whitespace, 0 otherwise
 */
int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * read_input - Reads the standard input and allocates memory.
 *
 * Return: The "cleaned" string with redundant characters removed.
 */
char *read_input(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	ssize_t chars_read;
	char *trim_start, *trim_end, *final_line;

	chars_read = getline(&buffer, &buffer_size, stdin);
	if (chars_read == -1)
	{
		free(buffer);
		return (NULL);
	}

	if (buffer[chars_read - 1] == '\n')
		buffer[chars_read - 1] = '\0';

	trim_start = buffer;
	while (*trim_start && is_whitespace(*trim_start))
		trim_start++;

	trim_end = trim_start + strlen(trim_start) - 1;
	while (trim_end > trim_start && is_whitespace(*trim_end))
		*trim_end-- = '\0';

	final_line = strdup(trim_start);
	free(buffer);

	return (final_line);
}
