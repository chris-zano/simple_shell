#include "shell.h"

/**
 * dash_execute - carries out the execution of commands
 *
 * @path: the path variables
 * @args: the tokenized arguments to be executed.
 *
 * Return: 0 Always.
 */

int dash_execute(char *path, char **args)
{
	pid_t cpid;
	int status;

	for (int i = 0; args[i] != NULL; i++)
		printf("arg is %s at \n", args[i]);
	if (strcmp(args[0], "exit") == 0)
	{
		return (dash_exit(args));
	}
	cpid = fork();
	if (cpid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror("dash:Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (cpid < 0)
	{
		perror("dash:Error");
	}
	else
	{
		waitpid(cpid, &status, WUNTRACED);
	}
	return (0);
}
