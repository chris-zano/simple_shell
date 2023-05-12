#include "shell.h"
/**
 * loop - the main loop that executes the shell.
 *
 * Return: void.
 */

void loop(void)
{
	char *line;
	char *buffer = NULL;
	size_t size = 0;
	ssize_t n;
	char **args;
	char *command;
	int status = 1;

	do {
		printf("~$ ");
		/* line = read_line(); */
		n = _getline(&buffer, &size, stdin);
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
		free(line);
		free(args);
	} while (status);
}
