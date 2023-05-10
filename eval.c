#include "shell.h"

void eval(char *buff)
{
    int bg;
    struct command cmd;

    printf("Evaluating '%s'\n", buff);

    bg = parse(buff, &cmd);
    //printf("Found command %s\n", cmd.argv[0]);

    if (bg = -1)
        return;
    if (cmd.argv[0] == NULL)
    {
        return;
    }
    if (cmd.builtin == NONE)
        runSystemCommand(&cmd, bg);
    else
        runSystemCommand(&cmd, bg);
}