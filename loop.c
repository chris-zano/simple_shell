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
	char *builtin_args[] = {"exit", "setenv", "unsetenv", "cd", "alias", NULL};

	do {
		write(0, "~$ ", 3);
		n = _getline(&buffer, &size, stdin);
		if (n == -1)
			break;
		args = split_line(buffer);

		if (is_builtin(args[0], args, builtin_args) == 0)
		{
			command = search_path(args);
			dash_execute(command, args);
		}
		free(args);
	} while (status);
}
