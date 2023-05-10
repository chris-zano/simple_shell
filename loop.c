#include "shell.h"

void loop()
{
    char *line;
    char **args;
    int status = 1;

    do
    {
        printf("~$ ");
        line = read_line();
        args = split_line(line);
        status = dash_execute(args);
        free(line);
        free(args);
    }
    while (status);
}