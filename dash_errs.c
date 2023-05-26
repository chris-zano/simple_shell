#include "shell.h"

/**
 *print_errorstr - prints an input string
 *
 * @str: the string to be printed
 *
 * Return: void
 */
void print_errorstr(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		write_errc(str[i]);
		i++;
	}
}

/**
 * write_errc - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 */
int write_errc(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == CLEAR_BUFFER || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != CLEAR_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == CLEAR_BUFFER || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != CLEAR_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string
 * @fd: the file to write to
 * Return: integer count of character put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
