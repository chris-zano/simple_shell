#include "shell.h"

/**
 * dash_logic - handles the && and || logical operators
 *
 * @args: command line arguments
 */
void dash_logic(char **args)
{
	int status;
	pid_t cpid;
	char *builtin_args[] = {"exit", "setenv", "unsetenv", "cd", "alias", NULL};
	char *command, *cmd;
	char **array, **tokens, *tok;
	int i = 0, j = 0, k = 0;
	int m;

	while (args[i])
		i++;
	command = calloc(1024, sizeof(char));

	for (int k = 0; args[k]; k++)
	{
		_strcat(command, args[k]);
		_strcat(command, " ");
	}
	array = malloc(1024);

	if (array == NULL)
	{
		free(command);
		return;
	}
	tok = _strtok(command, "||");
	while (tok != NULL)
	{
		array[i++] = tok;
		tok = _strtok(NULL, "||");
	}
	array[i] = NULL;

	while (j < i)
	{
		if (array[j])
		{
			tokens = split_line(array[j]);
			m = log_exec(tokens);
			if (m == 0)
			{
				return;
			}
		}
		j++;
	}
	free(command);
	free(array);
}

int log_exec(char **args)
{
	int status, val = 0;
	pid_t cpid;
	char *builtin_args[] = {"exit", "setenv", "unsetenv", "cd", "alias", NULL};
	char *path;

	cpid = fork();

	if (cpid == 0)
	{
		// execvp(args[0], args);
		if (is_builtin(args[0], args, builtin_args) == 0)
		{
			path = search_path(args);
			if (execve(path, args, environ) == -1)
			{
				perror("dash:Error");
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (cpid > 0)
	{
		waitpid(cpid, &status, 0);
	}
	else
	{
		perror("dash: Error forking process");
		return (-1);
	}

	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return -1;
	else
		return 0;
}