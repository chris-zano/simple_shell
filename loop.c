#include "shell.h"
/**
 * loop - the main loop that executes the shell.
 *
 * Return: void.
 */

void loop(void)
{
	char *buffer = NULL;
	size_t size = 0;
	ssize_t n;
	char **args;
	char *command;
	int status = 1;

	do {
		write(0,"~$ ",3);
		/* line = read_line(); */
		n = _getline(&buffer, &size, stdin);
		if (n == -1)
			exit(EXIT_FAILURE);
		args = split_line(buffer);
		if (strcmp(args[0], "exit") == 0)
		{
			dash_exit(args);
			return;
		}
		else
		{
			command = search_path(args);
			dash_execute(command, args);
		}
		free(args);
	} while (status);
}
