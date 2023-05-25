#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;
extern char *name;
extern int hist;
/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;
/**
 * struct built_in - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct built_in
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;
/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

alias_t *aliases;
ssize_t dash_getline(char **lineptr, size_t *n, FILE *stream);
void *dash_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **dash_strtok(char *line, char *delim);
char *_splitargs(char *line, int *exe_ret);
int _partargs(char **args, char **front, int *exe_ret);
char *_strcpy(char *dest, const char *src);
int _execargs(char **args, char **front, int *exe_ret);
int _parse_args(int *exe_ret);
char *dash_getenv(char *str);
char *cd_default(char **args);
int _strspn(char *s, char *accept);
int _ops_in_args(char **args);
void dash_freeargs(char **args, char **front);
char *search_path(char *command);
list_t *dash_split(char *path);
int _strlen(const char *s);
int dash_execute(char **args, char **front);
int _strncmp(const char *s1, const char *s2, size_t n);
void dash_freelist(list_t *head);
char *dash_toalpha(int num);
void dash_logic(char **line, ssize_t read);
void dash_replace(char **args, int *exe_ret);
char **replace_alias(char **args);
int (*dash_builtin(char *command))(char **args, char **front);
char *_strncat(char *dest, const char *src, size_t n);
char *_strchr(char *s, char c);
int dash_exit(char **args, char **front);
int dash_env(char **args, char __attribute__((__unused__)) **front);
int dash_setenv(char **args, char __attribute__((__unused__)) **front);
char *_strcat(char *dest, const char *src);
int create_error(char **args, int err);
int dash_unsetenv(char **args, char __attribute__((__unused__)) **front);
char *dash_errorenv(char **args);
char *dash_errortoexit(char **args);
char *alias_error(char **args);
int dash_cd(char **args, char __attribute__((__unused__)) **front);
int _strcmp(char *s1, char *s2);
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);
char *error_2_cd(char **args);
char **replace_alias(char **args);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);
void dash_freelist(list_t *head);
int proc_file_commands(char *file_path, int *exe_ret);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);
int filecommands(char *line, unsigned int line_size, int *ret);
void insert_spaces(const char *old_line, char *new_line);
void freenull(char *args);

#endif /* _SHELL_H_ */
