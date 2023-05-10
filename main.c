#include "shell.h"

int main(int argc, char *argv[])
{
    int MAXLINE = 1024;
    char buff[MAXLINE];
    char *prompt = ("$ ");

    while (1)
    {
        printf("%s", prompt);

        if ((fgets(buff, MAXLINE, stdin) == NULL) && ferror(stdin))
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        if (feof(stdin))
        {
            printf("\n");
            exit(0);
        }
        buff[strlen(buff) - 1] = '\0';
        eval(buff);
    }
    return (0);
}