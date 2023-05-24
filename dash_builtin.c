#include "shell.h"

/**
 * dash_builtin - maps builtin commands to their respective function pointers
 *
 * @command: builtin command
 *
 * @args: optional arguments for command
 *
 * Return: 0 (success), -1 (fail)
 */

int dash_builtin(char *command, char **args)
{
	int i = 0;
	int len = 0;
	builtinFunc func;

	builtin_t builtins[] = {
		{"exit", dash_exit},
		{"setenv", dash_setenv},
		{"unsetenv", dash_unsetenv},
		{"cd", dash_cd},
		{"alias", dash_alias}
	};

	len = sizeof(builtins) / sizeof(builtins[0]);

	for (i = 0; i < len; i++)
	{
		if (_strcmp(command, builtins[i].name) == 0)
		{
			func = builtins[i].func;
			func(args);

			return (0);
		}
	}

	return (-1);
}
