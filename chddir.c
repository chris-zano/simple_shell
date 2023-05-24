#include "shell.h"

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
		perror("./hsh: ");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("./hsh: ");
	}
}
