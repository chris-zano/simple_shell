#include "shell.h"

/**
 * search_path - searches the PATH for a file
 * Description: search the PATH env for a filename
 * it then concatenates the path to the filename and returna a pointer to the string
 * the string is then passed as an argument to the execve function
 *
 * Return: a pointer to a null terminated string containing the path of a file
 */

char *search_path(char **filename)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir;
	DIR *dp;
	struct dirent *entry;

	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable not set\n");
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		dp = opendir(dir);
		if (dp == NULL)
		{
			fprintf(stderr, "cannot open directory: %s\n", dir);
			continue;
		}

		while ((entry = readdir(dp)) != NULL)
		{
			if (_strcmp(entry->d_name, filename[0]) == 0)
			{
				dir = strcat(dir, "/");
				closedir(dp);
				return (strcat(dir, filename[0]));
			}
		}
		closedir(dp);
		dir = strtok(NULL, ":");
	}
	fprintf(stderr, "%s not found in PATH\n", filename[0]);
	return (NULL);
}
