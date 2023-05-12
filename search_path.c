#include "shell.h"


char *search_path(char **filename)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir;
	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable not set\n");
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		DIR *dp = opendir(dir);
		if (dp == NULL)
		{
			fprintf(stderr, "cannot open directory: %s\n", dir);
			continue;
		}

		struct dirent *entry;
		while ((entry = readdir(dp)) != NULL)
		{
			if (strcmp(entry->d_name, filename[0]) == 0)
			{
				printf("%s/%s\n", dir, filename[0]);
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
