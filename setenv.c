#include "shell.h"
#include "main.h"

/**
 * dash_setenv - sets the environment variables
 * @args: arguments array
 * Return: 0, always
 */

int dash_setenv(char **args)
{
	char *env = NULL;
	char **env_copy, *var;
	size_t count = 0;
	int i = 0;

	if (!args[1] || !args[2])
	{
		_printf("./hsh: %d: %s\n", errno, strerror(errno));
		return (-1);
	}
	var = malloc((_strlen(args[1])) + 1 + (_strlen(args[2])) + 1);

	if (var == NULL)
		return (-1);
	_strcpy(var, args[1]);
	_strcat(var, "=");
	_strcat(var, args[2]);
	env = _getenv(args[1]);

	if (!env)
	{
		free(env);
		env = var;
		return (0);
	}
	for (count = 0; environ[count]; count++)
		;
	env_copy = malloc(sizeof(char *) * (count + 1));

	if (env_copy == NULL)
	{
		free(var);
		return (-1);
	}
	for (i = 0; environ[i]; i++)
		env_copy[i] = _strdup(environ[i]);
	environ = env_copy;
	environ[i] = var;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * dash_unsetenv - unsets the environment variables
 * @args: arguments array
 * Return: 0, always
 */

int dash_unsetenv(char **args)
{
	char *var, **env_copy;
	size_t count = 0;
	int i, j;

	i = j = 0;

	if (!args[1])
	{
		_printf("./hsh: %d: %s\n", errno, strerror(errno));
		return (-1);
	}
	var = _getenv(args[1]);
	_printf("%s\n", var);

	if (!var)
		return (0);

	for (count = 0; environ[count]; count++)
		;
	env_copy = malloc(sizeof(char *) * (count + 1));

	if (!env_copy)
		return (-1);

	for (i = 0, j = 0; environ[i]; i++)
	{
		if (var == environ[i])
		{
			_printf("%s === %s\n", var, environ[i]);
			continue;
		}
		env_copy[j] = environ[i];
		j++;
	}
	environ = env_copy;
	environ[count - 1] = NULL;

	_printf("unsetenv function has been called\n");
	return (0);
}
