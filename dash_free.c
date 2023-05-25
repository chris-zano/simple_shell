#include "shell.h"

/**
 * dash_freeargs - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the start of args.
 */
void dash_freeargs(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @start: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string
 */
char *get_env_value(char *start, int len)
{
	char **addr;
	char *val = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, start, len);

	addr = _getenv(var);
	free(var);
	if (addr)
	{
		temp = *addr;
		while (*temp != '=')
			temp++;
		temp++;
		val = malloc(_strlen(temp) + 1);
		if (val)
			_strcpy(val, temp);
	}

	return (val);
}

/**
 * dash_replace - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last dash_executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last dash_executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void dash_replace(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *val = NULL, *pl = *line, *nl;

	for (j = 0; pl[j]; j++)
		if (pl[j] == '$' && pl[j + 1] &&
				pl[j + 1] != ' ')
		{
			if (pl[j + 1] == '$')
			{
				val = get_pid();
				k = j + 2;
			}
			else if (pl[j + 1] == '?')
			{
				val = dash_toalpha(*exe_ret);
				k = j + 2;
			}
			else if (pl[j + 1])
			{
				for (k = j + 1; pl[k] && pl[k] != '$' && pl[k] != ' '; k++)
					;
				len = k - (j + 1);
				val = get_env_value(&pl[j + 1], len);
			}
			nl = malloc(j + _strlen(val) + _strlen(&pl[k]) + 1);
			if (!line)
				return;
			nl[0] = '\0';
			_strncat(nl, pl, j);
			if (val)
			{
				_strcat(nl, val);
				free(val);
				val = NULL;
			}
			_strcat(nl, &pl[k]);
			free(pl);
			pl = *line = nl;
			j = -1;
		}
}
