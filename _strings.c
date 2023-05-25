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

/**
 * _strcmp - compares two strings.
 *
 * @str1: the first string.
 * @str2: the second string.
 *
 * Return: zero if str1==str2, positive is str1>str2 and negative if str1<str2.
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

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
