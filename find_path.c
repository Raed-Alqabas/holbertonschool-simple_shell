#include "shell.h"

/**
 * find_path - Finds the full path of a command using PATH environment variable
 * @cmd: The command name to search for
 *
 * Return: Full path if found, NULL otherwise
 */
char *find_path(char *cmd)
{
    char *env_path, *env_path_dup, *directory;
    char constructed_path[1024];
    struct stat file_info;

    if (!cmd)
        return (NULL);

    /* Check if command is already a path (absolute or relative) */
    if (cmd[0] == '/' || strncmp(cmd, "./", 2) == 0 || strncmp(cmd, "../", 3) == 0)
    {
        if (stat(cmd, &file_info) == 0)
            return (strdup(cmd));
        else
            return (NULL);
    }

    env_path = _getenv("PATH");
    if (!env_path || env_path[0] == '\0')
        return (NULL);

    env_path_dup = strdup(env_path);
    if (!env_path_dup)
        return (NULL);

    directory = strtok(env_path_dup, ":");
    while (directory)
    {
        if (strlen(directory) == 0)
            snprintf(constructed_path, sizeof(constructed_path), "./%s", cmd);
        else
            snprintf(constructed_path, sizeof(constructed_path), "%s/%s", directory, cmd);

        if (stat(constructed_path, &file_info) == 0)
        {
            free(env_path_dup);
            return (strdup(constructed_path));
        }

        directory = strtok(NULL, ":");
    }

    free(env_path_dup);
    return (NULL);
}
