#include "shell.h"

/**
 * dash_builtin - Matches a command with a corresponding
 *               dash builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*dash_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{"env", dash_env},
		{"exit", dash_exit},
		{"cd", dash_cd},
		{"setenv", dash_setenv},
		{"unsetenv", dash_unsetenv},
		{NULL, NULL}};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * dash_exit - Causes normal process termination
 *                for the dash shell.
 * @args: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int dash_exit(char **args, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	dash_freeargs(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}
#include "shell.h"

/**
 * create_path - removes leading characters up to the =
 *
 * @str: the string / path
 *
 * Return: the path, or empty string
 */

char *create_path(char *str)
{
	char *c = _strchr(str, '=');

	if (c != NULL)
		return (c + 1);
	return ("");
}

/**
 * dash_cd - Changes the current directory of the dash process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int dash_cd(char **args, char __attribute__((__unused__)) **front)
{
	char *dir = args[1];

	if (!dir)
	{
		dir = create_path(dash_getenv("HOME"));

		if (!dir)
		{
			perror("./hsh: Error");
			return (-1);
		}
	}
	if (_strcmp(dir, "-") == 0)
	{
		dir = create_path(dash_getenv("OLDPWD"));

		if (!dir)
		{
			perror("./hsh: Error");
			return (-1);
		}
	}
	return (0);
}
