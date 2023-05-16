#include "shell.h"

/**
 * _strlen - returns the length of a string
 *
 * @s: a pointer to a string
 *
 * Return: length of string
 */

int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);

	for (len = 0; s[len]; len++)
		;
	return (len);
}
