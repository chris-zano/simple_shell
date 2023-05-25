#include "shell.h"
#include "main.h"

/**
 * read_line - reads a line from standard input
 * Description: A custom implementation of the getline function
 * Return: a pointer to the characters read from stdin
 */

char *read_line()
{
	int buffsize = 1024;
	int position = 0;
	char *buffer = malloc(sizeof(char) * buffsize);
	int c;

	if (!buffer)
	{
		_printf("./hsh: %d: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		c = getchar();
		if (c == EOF)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
		{
			buffer[position] = c;
		}
		position++;

		if (position >= buffsize)
		{
			buffsize += 1024;
			buffer = realloc(buffer, sizeof(char) * buffsize);
			if (!buffer)
			{
				_printf("./hsh: %d: %s\n", errno, strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
	}
	free(buffer);
}
