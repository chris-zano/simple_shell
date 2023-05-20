#include "shell.h"

char **call_cmds(char *line)
{
	char *tok = _strtok(line, ";");
	char **args = malloc(_strlen(line));
	char **cmds, *cmd;
	char *builtin_args[] = {"exit", "setenv", "unsetenv", "cd", "alias", NULL};
	int i = 0, j;
	while (tok != NULL)
	{
		printf("%d => %s\n", i, tok);
		args[i] = tok;
		tok = _strtok(NULL, ";");
		i++;
	}

	j = 0;
	for (j = 0; j != i; j++)
	{
		cmds = split_line(args[j]);

		return (cmds);
	}
}
