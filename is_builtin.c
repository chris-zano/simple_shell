#include "shell.h"

/**
 * is_builtin - checks if command input is a builtin command
 *
 * @command: the input command
 *
 * @builtin_args: an array of possible builtin commands
 *
 * Description: it checks if command is a builtin command,
 * if there is a macth, it then calls the dash_builtin function
 * with the command as an argument. The dash_builtin function then
 * calls a process that executes the command
 *
 * Return: 1 if match, 0 otherwise
 */

int is_builtin(char *command, char **builtin_args)
{
	int i = 0;
	int len = sizeof(builtin_args) / sizeof(builtin_args[0]);

	for (i = 0; i < len; i++)
	{
		if (_strcmp(command, builtin_args[i]) == 0)
		{
			dash_builtin(command);
			return (1);
		}
	}
	return (0);
}
