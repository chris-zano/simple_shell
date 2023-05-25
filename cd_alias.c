#include "shell.h"
#include "main.h"

/**
 * create_path - removes leading characters up to the =
 *
 * @str: the string / path
 *
 * Return: the path, or empty string
 */

char *create_path(char *str)
{
	char *c = strchr(str, '=');

	if (c != NULL)
		return (c + 1);
	return ("");
}

/**
 * cd_default - sets the directory when no args are passed
 *
 * @args: array of arguments
 *
 * Return: the directory
 */

char *cd_default(char **args)
{
	char *dir = args[1];

	if (!dir)
	{
		dir = create_path(_getenv("HOME"));

		if (!dir)
		{
			_printf("./hsh: %d: %s\n", errno, strerror(errno));
			return (NULL);
		}
	}
	if (_strcmp(dir, "-") == 0)
	{
		dir = create_path(_getenv("OLDPWD"));

		if (!dir)
		{
			_printf("./hsh: %d: %s\n", errno, strerror(errno));
			return (NULL);
		}
	}
	return (dir);
}

/**
 * dash_cd - changes the directory
 *
 * @args: array of arguments to pass tot he function
 *
 * Return: 0 on success, 1 on failure
 */

int dash_cd(char **args)
{
	char *cwd, *setenv_args[] = {NULL, NULL};
	int cdir = 0;

	cdir = chdir(cd_default(args));

	if (cdir != 0)
	{
		_printf("./hsh: %d: %s\n", errno, strerror(errno));
		return (1);
	}
	cwd = getcwd(NULL, 0);

	if (!cwd)
	{
		_printf("./hsh: %d: %s\n", errno, strerror(errno));
		free(cwd);
		return (1);
	}
	setenv_args[0] = "PWD";
	setenv_args[1] = cwd;
	cdir = dash_setenv(setenv_args);

	if (cdir != 0)
	{
		_printf("./hsh: %d: %s\n", errno, strerror(errno));
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}
