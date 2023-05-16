#include "shell.h"

/**
 * _strncmp - compare n bytes of two strings
 *
 * @str1: pointer to destination string
 *
 * @str2: pointer to source string
 *
 * @n: the first n bytes of the strings to compare
 *
 * Return: 0 if there is a match
 * else return - (-1) if str1 < str2
 * else return - (1) if str1 > str2
 */

int _strncmp(const char *str1, const char *str2, size_t n)
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
