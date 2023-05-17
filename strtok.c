#include "shell.h"

/**
 * _strtok - splits a string into words
 *
 * @str: string to split.
 * @delim: an array of delimeters.
 *
 * Return: an array of strings (Success) or NULL (Error)
 */

char *_strtok(char *str, char *delim)
{
	static char *olds;
	char *token;
	size_t n = 1024;

	if (str == NULL)
		str = olds;

	str += _strspn(str, delim);
	if (*str == '\0')
	{
		olds = str;
		return (NULL);
	}

	token = str;
	str = _strpbrk(token, delim);
	if (str == NULL)
		olds = _memchr(token, '\0', n);
	else
	{
		*str = '\0';
		olds = str + 1;
	}
	return (token);
}
