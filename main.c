#include "shell.h"
/**
 * main - entry point of the program.
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 Always.
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char command[1024], **args;
	char *builtin_args[] = {"exit", "setenv", "unsetenv", "cd", "alias", NULL};
	int retcal;

	if (argc != 2)
		loop();
	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			printf("Error opening file: %s\n", argv[1]);
			return (1);
		}
		while (fgets(command, sizeof(command), file) != NULL)
		{
			args = split_line(command);
			if (args[0] == NULL)
			{
				retcal = _split(command);
				if (retcal == 0)
					continue;
				else
					break;
			}
			else
			{
				search_execute(args, builtin_args);
			}
		}
		fclose(file);
	}
	return (0);
}
