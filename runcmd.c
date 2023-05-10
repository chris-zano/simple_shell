#include "shell.h"

void runSystemCommand(struct command *cmd, int bg)
{
    pid_t childpid;

    if ((childpid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (childpid == 0)
        {
            if (execvp(cmd->argv[0], cmd -> argv) < 0)
                {
                    printf("%s: Command not found\n", cmd -> argv[0]);
                    exit(0);
                }
        }
    else {
        if (bg)
            {
                printf("Child process background [%d]\n", childpid);
            }
            else
                wait(&childpid);
    }
}