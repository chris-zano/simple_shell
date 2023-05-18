#include "shell.h"

/**
 * _strcpy - copies the string pointed to by src including '\0'
 *
 * @dest: destination string
 * @src: source to copy from
 *
 * Return: destination string, else NULL
 */

char *_strcpy(char *dest, char *src)
{
	size_t i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
