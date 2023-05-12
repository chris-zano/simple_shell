#include "shell.h"

char *read_line()
{
    int buffsize = 1024;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "%sdash: Allocation errors%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= buffsize)
        {
            buffsize += 1024;
            buffer = realloc(buffer, sizeof(char) * buffsize);
            if (!buffer)
            {
                fprintf(stderr, "%sdash: Allocation errors%s\n", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }
        
    }
}