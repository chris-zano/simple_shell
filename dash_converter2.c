#include "shell.h"

/**
 * cont_add - continue chaining based on last status
 * @data: struct
 * @buf: buffer
 * @p: addressposition in buf
 * @i: start
 * @len: length
 * Return: Void
 */
void cont_add(unistruct_t *data, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (data->cbuffer_type == SET_LOG)
	{
		if (data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (data->cbuffer_type == SET_CON)
	{
		if (!data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}
/**
 * _checkdelim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _checkdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_check_c - checks if character
 *@c: input
 *Return: 1 if true, 0 (fail)
 */

int _check_c(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 (success)
 */

int _atoi(char *s)
{
	int i, neg = 1, f = 0, ret_val;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && f != 2; i++)
	{
		if (s[i] == '-')
			neg *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			f = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (neg == -1)
		ret_val = -result;
	else
		ret_val = result;

	return (ret_val);
}
