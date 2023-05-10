#include "main.h"

int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	char **words, *cmd = NULL;
	int i = 0, status, count;
	pid_t pid;
	
	if (argc == 2)
	{
		/* handle file as input */
		printf("Feature not yet implemented\n");
	}

	while (1)
	{
		printf("$ ");
		fflush(stdout);
		nread = _getline(&line, &size, stdin);
		if (nread == -1)
		{
			printf("\n");
			break;
		}

		/*printf("%s", line);*/
		words = _strtok(line);
		i = count = 0;
		while (words[i] != NULL)
		{
			count++;
			i++;
		}
		words[count] = NULL;
		printf("count = %d\n", count);
		cmd = search_path(words[0]);
		printf("return command is %s\n", cmd);

		if (cmd != NULL)
		{
			pid = fork();
			if (pid == -1)
				perror("(./hsh)Error: ");
			else if (pid == 0)
			{
				if (execve(cmd, words, environ) == -1)
				{
					perror("./hsh(Error): ");
					exit(1);
				}
			}
			else
				wait(&status);
		}
	}
	free(line);
	return 0;
}
