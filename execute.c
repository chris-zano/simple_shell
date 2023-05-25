#include "shell.h"
#include "main.h"

/**
 * dash_execute - carries out the execution of commands
 *
 * @path: the path variables
 * @args: the tokenized arguments to be executed.
 *
 * Return: 0 Always.
 */

int dash_execute(char *path, __attribute__((unused))char **args)
{
	pid_t cpid;
	int status;

	cpid = fork();
	if (cpid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			_printf("./hsh: %d: %s\n", errno, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else if (cpid < 0)
	{
		_printf("./hsh: %d: %s\n", errno, strerror(errno));
		return (-1);
	}
	else
	{
		waitpid(cpid, &status, WUNTRACED);
	}
	/* free(args);*/
	return (0);
}
