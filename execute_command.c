#include "main.h"


void execute_command(char *path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: ");
		return;
	}
	else if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror("(./hsh)Error");
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}
