#include "shell.h"

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
	while (*str1 && str2)
	{
		if (str1 != str2)
			return (*str1 - str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 > *str2 ? 1 : -1);
}
