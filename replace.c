#include "shell.h"

/**
 * replace_variables - handles the variable replacement $ $$
 *
 * @line: pointer to the line buffer
 * @exit_status: the exit status of the process
 *
 * Return: pointer to the replacement
*/
char *replace_variables(char *line, int exit_status)
{
char *result = malloc(strlen(line) * sizeof(char));
char *token;
char *variable;
char *replacement;
int replaced = 0;

_strcpy(result, line);
token = _strtok(result, " ");

while (token != NULL)
{
if (_strcmp(token, "$?") == 0)
{
char status_str[16];
sprintf(status_str, "%d", exit_status);
replacement = _strdup(status_str);
replaced = 1;
}
else if (_strcmp(token, "$$") == 0)
{
char pid_str[16];
sprintf(pid_str, "%d", getpid());
replacement = _strdup(pid_str);
replaced = 1;
}
else
{
token = _strtok(NULL, " ");
continue;
}
variable = strstr(result, token);
memmove(variable + _strlen(replacement), variable + _strlen(token),
_strlen(variable + _strlen(token)) + 1);
strncpy(variable, replacement, _strlen(replacement));
free(replacement);
token = _strtok(NULL, " ");
}
if (replaced)
return (result);
else
{
free(result);
return (line);
}
}
