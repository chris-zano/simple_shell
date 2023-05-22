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
	char *buffer = NULL, *tok, *buf_cpy;
	size_t size = 0;
	ssize_t n;
	char **args, **cmds;
	char *command;
	int status = 1, i = 0, j = 0, count = 0;
	char *builtin_args[] = {"exit", "setenv", "unsetenv", "cd", "alias", NULL};

	do {
		write(0, "~$ ", 3);
		n = _getline(&buffer, &size, stdin);
		if (n == -1)
			break;
		args = split_line(buffer);
		printlog(args);

		if (args[0] == NULL)
		{
			buf_cpy = _strdup(buffer);
			cmds = malloc((size + 1) * sizeof(char *));
			tok = _strtok(buf_cpy, ";");

			while(tok != NULL)
			{
				cmds[i] = tok;
				tok = _strtok(NULL, ";");
				i++;
			}
			cmds[i] = NULL;
			for (j = 0; j < i; j++)
			{
				args = split_line(cmds[j]);
				if (args != NULL)
				{
					search_execute(args, builtin_args);
					free(args);
				}
			}
			free(cmds);
			free(buf_cpy);
		}
		else
		{
			printlog(args);
			search_execute(args, builtin_args);
			free(args);
		}
		free(buffer);
	} while (status);
}
