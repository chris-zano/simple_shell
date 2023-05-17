#include "shell.h"

/**
 * remove_prefix - removes prefix from the path
 *
 * @path: the PATH from environment
 * @prefix: the prefix to be removed
 *
 * Return: new path without prefix, else NULL
 */

char *remove_prefix(char *path, char *prefix)
{
	size_t len = _strlen(prefix);

	if (_strncmp(path, prefix, len) == 0)
		return (_strdup(path + len));
	return (NULL);
}

/**
 * search_path - searches the PATH for a file
 *
 * Description: search the PATH env for a filename
 * it then concatenates the path to the filename
 * and returna a pointer to the string
 * the string is then passed as an argument to the execve function
 *
 * @filename: the name of the file to search for in the PATH
 *
 * Return: a pointer to a null terminated string containing the path of a file
 */

char *search_path(char **filename)
{
	char *prefix = "PATH=";
	char *path = _getenv("PATH");
	char *path_copy;
	char *dir;
	DIR *dp;
	struct dirent *entry;

	if (path == NULL)
	{
		perror("dash:Error path is null");
		return (NULL);
	}

	path = remove_prefix(path, prefix);
	path_copy = _strdup(path);
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		dp = opendir(dir);
		if (dp == NULL)
		{
			perror("dash:Error failed to open dir");
			continue;
		}

		while ((entry = readdir(dp)) != NULL)
		{
			if (_strcmp(entry->d_name, filename[0]) == 0)
			{
				dir = _strcat(dir, "/");
				closedir(dp);
				return (_strcat(dir, filename[0]));
			}
		}
		closedir(dp);
		dir = strtok(NULL, ":");
	}
	return (NULL);
}
