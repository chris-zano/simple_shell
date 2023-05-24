#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

/* macro definitions */
#define BUFFER_SIZE 1024
#define TOK_DELIM " \t\r\n"
#define TK_BUFF_SIZE 1024
#define MAX_ALIAS 100
#define MAX_ALIAS_LEN 100


extern char **environ;
/* struct declarations go here */

typedef void (*ExecuteCb)(char **str);
typedef int (*builtinFunc)(char **args);

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

/**
 * struct alias_s - struct definition for alias
 *
 * @name: name of alias
 *
 * @value: value of alias assignment
 */

typedef struct alias_s 
{
	char name[MAX_ALIAS_LEN];
	char value[MAX_ALIAS_LEN];
} alias_t;



/* function declarations go here */
char *read_line();
char **split_line(char *);
char *search_path(char **filename);
int dash_execute(char *path, char **args);
int dash_exit(char **args);
void loop(void);
char *_strtok(char *str, char *delim);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _strcmp(char *str1, char *str2);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
char *_getenv(char *str);
int _strncmp(char *str1, char *str2, size_t n);
int _strlen(char *str);
int dash_builtin(char *command, char **args);
int is_builtin(char *command, char **args, char **builtin_args);
int dash_setenv(char **args);
int dash_unsetenv(char **args);
char *remove_prefix(char *path, char *prefix);
char *_strcpy(char *dest, char *src);
void *_memchr(void const *s, int c_in, size_t n);
size_t _strspn(const char *str1, const char *str2);
char *_strpbrk(const char *s, const char *accept);
int dash_cd(char **args);
int dash_alias(char **args);
char *create_path(char *str);
char *cd_default(char **args);
void search_execute(char **args, char **builtin_args);
void printlog(char **strarr);
void dfree(char **dptr);
void dash_logic(char **args);
char *replace_variables(char *line, int exit_status);
int _split(char *buffer);
int log_exec(char **args);

#endif /* SHELL_H */
