#include "shell.h"

/**
 * _strspn - Returns the length of the initial portion of
 * str1 which consists only of characters that are part of str2
 *
 * @s: input
 * @accept: input
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
		else
			++count;
	}
	return (count);
}
