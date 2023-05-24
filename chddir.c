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
		perror("cd: missing argument\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("Error: cd");
	}
}
