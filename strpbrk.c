#include "shell.h"

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
	  return (char *) s;
      ++s;
    }

  return NULL;
}
