#include "shell.h"

/**
 * _strncmp - compare n bytes of two strings
 *
 * @str1: pointer to destination string
 * @str2: pointer to source string
 * @n: the first n bytes of the strings to compare
 * Return: 0 if there is a match
 * else return - (-1) if str1 < str2
 * else return - (1) if str1 > str2
 */

int _strncmp(char *str1, char *str2, size_t n)
{
	size_t i = 0;

	for (i = 0; (str1[i] && str2[i] && i < n); i++)
	{
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
	}

	if (i == n)
		return (0);
	return (-1);
}

/**
 * _strpbrk - finds the first occurrence in S of any character in accept.
 *
 * @s: the string whose length to check
 * @accept: the string to be checked.
 *
 * Return: integer length of string
 */

char *_strpbrk(const char *s, const char *accept)
{
	while (*s != '\0')
	{
		const char *a = accept;

		while (*a != '\0')
			if (*a++ == *s)
				return ((char *)s);
		++s;
	}
	return (NULL);
}

/**
 * _strspn - Returns the length of the initial portion of
 * str1 which consists only of characters that are part of str2
 *
 * @str1: input
 * @str2: input
 *
 * Return: Always 0 (Success)
 */

size_t _strspn(const char *str1, const char *str2)
{
	const char *p;
	const char *a;
	size_t count = 0;

	for (p = str1; *p != '\0'; ++p)
	{
		for (a = str2; *a != '\0'; ++a)
		{
			if (*p == *a)
				break;
		}
		if (*a == '\0')
			return (count);
		++count;
	}
	return (count);
}

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

