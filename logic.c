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
	char *command;

	cpid = fork();

	if (cpid == 0)
	{
		// execvp(args[0], args);
		if (is_builtin(args[0], args, builtin_args) == 0)
		{
			command = search_path(args);
			dash_execute(command, args);
		}
		perror("dash: Error executing command");
		exit(EXIT_FAILURE);
	}
	else if (cpid > 0)
	{
		waitpid(cpid, &status, 0);
		if (status == 0 && args[1] != NULL && _strcmp(args[1], "&&") == 0)
		{
			dash_logic(&args[2]);
		}
		else if (status != 0 && args[1] != NULL && _strcmp(args[1], "||") == 0)
		{
			dash_logic(&args[2]);
		}
		else if (status < 0)
		{
			perror("dash: Error executing command");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		perror("dash: Error forking process");
	}
}
