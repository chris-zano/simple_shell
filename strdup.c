#include "shell.h"

/**
 * _strdup - duplicate to new memory space location
 * @str: char
 * Return: 0
 */

char *_strdup(char *str)
{
	char *cpy;
	int i, r = 0;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
		i++;

	cpy = malloc(sizeof(char) * (i + 1));

	if (cpy == NULL)
		return (NULL);

	for (r = 0; str[r]; r++)
		cpy[r] = str[r];
	return (cpy);
}
