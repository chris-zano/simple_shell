#include "shell.h"

/**
 * _strcat - concatenates two strings.
 *
 * @dest: a pointer to the destination buffer.
 * @src: the string to be appended.
 *
 * Return: a pointer to dest.
 */

char *_strcat(char *dest, char *src)
{
	char *buff = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (buff);
}
