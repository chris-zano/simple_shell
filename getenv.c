#include "shell.h"

/**
 * _getenv - fetches the environment variable from PATH
 *
 * @str: name of the environment variable to fetch
 *
 * Return: pointer to environment variable, else NULL
 */

char **_getenv(char *str)
{
	int i = 0;
	int len = _strlen(str);

	for (i = 0; environ[i]; i++)
		if (_strncmp(str, environ[i], len) == 0)
			return (&environ[i]);
	return (NULL);
}
