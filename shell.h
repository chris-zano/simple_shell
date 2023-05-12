#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

/* macro definitions */
#define BUFFER_SIZE 1024
#define TOK_DELIM " \t\r\n"
#define TK_BUFF_SIZE 1024
#define RED "\033[0;31m"
#define RESET "\e[0m"

extern char **environ;

/* function declarations go here */
char *read_line();
char **split_line(char *);
char *search_path(char **filename);
int dash_execute(char *path, char **args);
int dash_exit(char **args);
void loop();

#endif /* SHELL_H */
