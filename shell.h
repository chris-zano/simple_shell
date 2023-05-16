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

/* struct declarations go here */

typedef int (*builtinFunc)();

/**
 * struct built_in - struct definition for builtin commands
 *
 * @name: name of the builtin
 *
 * @func: fuction pointer to execute the builtin command
 */

typedef struct built_in
{
	char *name;
	builtinFunc func;
} builtin_t;

/* function declarations go here */
char *read_line();
char **split_line(char *);
char *search_path(char **filename);
int dash_execute(char *path, char **args);
int dash_exit(char **args);
void loop(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _strcmp(char *str1, char *str2);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
char **_getenv(char *str);
int _strncmp(const char *str1, const char *str2, size_t n);
int _strlen(char *str);
int dash_builtin(char *command);
int is_builtin(char *command, char **builtin_args);
int dash_setenv(void);
int dash_unsetenv(void);

#endif /* SHELL_H */
