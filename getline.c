#include "shell.h"

/**
 * _getline - reads a line from stdin
 * @lineptr: pointer to an array containing line read
 * @n: number of bytes read from stream
 * @stream: the stream where the line is read from
 * Return: the number of characters read, -1 (fail)
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char *buf = NULL;
	size_t bufsize = 0;
	size_t pos = 0;
	int c;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);

	if (*lineptr == NULL)
	{
		bufsize = BUFFER_SIZE;
		buf = (char *)malloc(bufsize);
		if (buf == NULL)
			return (-1);
	}
	else
	{
		buf = *lineptr;
		bufsize = *n;
	}
	while ((c = fgetc(stream)) != EOF)
	{
		if (pos + 1 >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			buf = (char *)realloc(buf, bufsize);
			if (buf == NULL)
				return (-1);
		}
		buf[pos++] = c;
		if (c == '\n')
			break;
	}
	if (pos == 0)
		return (-1);
	buf[pos] = '\0';
	*lineptr = buf;
	*n = bufsize;
	return (pos);
}
