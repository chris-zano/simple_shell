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
			perror("dash:Error: cd");
			return (NULL);
		}
	}
	if (_strcmp(dir, "-") == 0)
	{
		dir = create_path(_getenv("OLDPWD"));

		if (!dir)
		{
			perror("dash:Error: cd");
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
		perror("dash:Error: cd");
		return (1);
	}
	cwd = getcwd(NULL, 0);

	if (!cwd)
	{
		perror("dash:Error: cd");
		return (1);
	}
	setenv_args[0] = "PWD";
	setenv_args[1] = cwd;
	cdir = dash_setenv(setenv_args);

	if (cdir != 0)
	{
		perror("dash:Error: cd");
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}

int dash_alias(char **args)
{
	alias_t alias[MAX_ALIAS];
	int count = 0, i = 0, j = 0;
	char *name, *value;

	if (!args[1])
		for (i = 0; i < count; i++)
		{
			printf("%s='%s'\n", alias[i].name, alias[i].value);
			free(alias[i].name);
			free(alias[i].value);
		}
	else
	{
		for (i = 1; args[i]; i++)
		{
			name = _strtok(args[i], "=");
			value = _strtok(NULL, "=");

			if (value = NULL)
				for (j = 0; j < count; j++)
				{
					if (_strcmp(alias[j].name, name) == 0)
					{
						printf("%s='%s'\n", alias[j].name, alias[j].value);
						free(alias[j].name);
						free(alias[j].value);
						break;
					}
				}
			else
			{
				j = 0;
				for (j = 0; j < count; j++)
				{
					if (_strcmp(alias[j].name, name) == 0)
					{
						_strcpy(alias[j].value, value);
						break;
					}
				}
			}
			if (j = count)
			{
				if (count >= MAX_ALIAS)
				{
					perror("Error: maximum length reached");
					return (-1);
				}
				_strcpy(alias[count].name, name);
				_strcpy(alias[count].value, value);
				count++;
			}
		}
	}
	return (0);
}


