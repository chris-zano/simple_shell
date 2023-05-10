#include "shell.h"

int parse(const char *buff, struct command *cmd)
{
    int MAXLINE = 1024;
    char array[MAXLINE];
    const char delims[10] = " \t\r\n";
    char *line = array;
    char *token;
    char *endline;
    int is_bg;

    if (buff == NULL)
    {
        perror("The commandline is NULL");

    }
    strncpy(line, buff, MAXLINE);
    endline = line + strlen(line);

    cmd -> argc = 0;

    while (line < endline)
        {
            line += strspn(line, delims);
            if (line >= endline)
            {
                break;
            }
            token = line + strcspn (line, delims);

            *token = '\0';
            cmd -> argv[cmd -> argc] = line;

            if (cmd -> argc++ >= MAX_ARGS - 1)
            {
                break;
            }
            line = token + 1;
        }
    cmd -> argv[cmd -> argc] = NULL;

    if (cmd ->argc == 0)
    {
        return 1;
    }
    cmd -> builtin = parseBuiltin(cmd);

    if ((is_bg = (*cmd -> argv[cmd->argc - 1] == '&')) != 0)
        cmd -> argv[--cmd -> argc] == NULL;
    return is_bg;
}