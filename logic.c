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

	cpid = fork();

	if (cpid == 0)
	{        
		execvp(args[0], args);
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
	}
	else
	{
		perror("dash: Error forking process");
	}
}
