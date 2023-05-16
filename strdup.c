#include "shell.h"

/**
 * _strdup - duplicate to new memory space location
 * @str: char
 * Return: 0
 */

char *_strdup(char *str)
{
	size_t len = _strlen(str) + 1;
	void *new = malloc(len);

	if (new == NULL)
		return (NULL);

	return ((char *) memcpy(new, str, len));
}
