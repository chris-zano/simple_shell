#include "shell.h"
#include "main.h"

/**
 * _cd - a function that changes the directory.
 *
 * @args: a pointer to an array of string.
 *
 * Return: NULL
 */

void _cd(char **args)
{
	if (args[1] == NULL)
	{
		_printf("./hsh: %d: %s\n", errno, strerror(errno));
	}
	else
	{
		if (chdir(args[1]) != 0)
			_printf("./hsh: %d: %s\n", errno, strerror(errno));
	}
}
