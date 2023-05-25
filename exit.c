#include "shell.h"

/**
 * dash_exit - to function that exits the shell.
 *
 * @args: arguments passed by the user.
 *
 * Return: 0 Always.
 */

int dash_exit(__attribute__((unused))char **args)
{
	int len = 0;

	while (args[len] != NULL)
		len++;

	if (len > 1)
		_exit(atoi(args[1]));
	else
		_exit(EXIT_SUCCESS);
}
