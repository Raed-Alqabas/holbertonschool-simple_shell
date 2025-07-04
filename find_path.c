#include "shell.h"

/**
 * _getenv - Get the environment variable value
 * @var_name: The variable name to search
 *
 * Return: Pointer to value or NULL
 */
char *_getenv(const char *var_name)
{
	int index;
	size_t name_len = strlen(var_name);

	for (index = 0; environ[index]; index++)
	{
		if (strncmp(environ[index], var_name, name_len) == 0 &&
		    environ[index][name_len] == '=')
			return (environ[index] + name_len + 1);
	}
	return (NULL);
}

/**
 * find_in_path - Searches for a command in PATH
 * @cmd_name: Command to search
 *
 * Return: Full path if found and executable, NULL otherwise
 */
char *find_path(const char *cmd_name)
{
	char *path_value = _getenv("PATH");
	char *path_copy, *current_dir;
	char path_candidate[1024];

	if (path_value == NULL || *path_value == '\0')
		return (NULL);

	path_copy = strdup(path_value);
	if (!path_copy)
		return (NULL);

	current_dir = strtok(path_copy, ":");
	while (current_dir != NULL)
	{
		snprintf(path_candidate, sizeof(path_candidate), "%s/%s", current_dir, cmd_name);
		if (access(path_candidate, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(path_candidate));
		}
		current_dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
