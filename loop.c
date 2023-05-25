#include "shell.h"

/**
 * search_execute - searches for a command and executes
 *
 * @args: command arguments
 * @builtin_args: builtin args array
 *
 * Return: exexute the command
 */

void search_execute(char **args, char **builtin_args)
{
	char *command;
	int k = 0;

	for (k = 0; args[k]; k++)
	{
		if (_strcmp(args[k], "||") == 0)
		{
			dash_logic(args);
			return;
		}
		if (_strcmp(args[k], "&&") == 0)
		{
			dash_logic(args);
			return;
		}
	}
	if (is_builtin(args[0], args, builtin_args) == 0)
	{
		command = search_path(args);
		dash_execute(command, args);
	}
}
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
	char *builtin_args[] = {"exit", "setenv", "unsetenv", "cd", "alias", NULL};
	int retcal;
	int status = 1;

	do {
		write(0, "~$ ", 3);
		n = _getline(&buffer, &size, stdin);
		if (n == -1)
			break;

		/* line = replace_variables(buffer, exit_status)*/
		args = split_line(buffer);

		if (args[0] == NULL)
		{
			retcal = _split(buffer);
			if (retcal == 0)
				continue;
			else
				break;
		}
		else
		{
			search_execute(args, builtin_args);
		}
		/* free(buffer);*/
	} while (status);
}
