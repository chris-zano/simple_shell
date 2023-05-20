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
	char *buffer = NULL, *tok;
	size_t size = 0;
	ssize_t n;
	char **args, **cmds;
	char *command;
	int status = 1, i = 0, j = 0;
	char *builtin_args[] = {"exit", "setenv", "unsetenv", "cd", "alias", NULL};

	do {
		write(0, "~$ ", 3);
		n = _getline(&buffer, &size, stdin);
		if (n == -1)
			break;
		args = split_line(buffer);

		if (args == NULL)
		{
			cmds = malloc(_strlen(buffer));
			tok = _strtok(buffer, ";");

			while(tok != NULL)
			{
				cmds[i] = tok;
				tok = _strtok(NULL, ";");
				i++;
			}
			for (j = 0; j != i; j++)
			{
				args = split_line(cmds[j]);
				search_execute(args, builtin_args);
			}
		}
		else
			search_execute(args, builtin_args);
		free(args);
		free(cmds);
	} while (status);
}
