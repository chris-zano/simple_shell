#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/types.h>

#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define CLEAR_BUFFER -1
#define RESET_CHAR_LOWER	1
#define RESET_DEF	0
#define SET_CON		1
#define USE_STRTOK 0
#define HISTORY_FILE_LIST	".dash_history"
#define HIST_MAX	4096
#define SET_COM	3
#define SET_LOG		2
#define RESET_NON_NEG	2
#define GETLINE_DEF 0
/**
 * struct dashlist_s - linked list
 * @num: number
 * @str: string
 * @next: next node
 */
typedef struct dashlist_s
{
	int num;
	char *str;
	struct dashlist_s *next;
} dash_t;

/**
 *struct customdata - allowing uniform prototyping
 *@arg: a string
 *@argv: an array
 *@path: a string path
 *@argc: the argument count
 *@line_count: the error count
 *@error_coden: the error code
 *@lc_flag: count line
 *@fname: filename
 *@env: copy of environ
 *@environ: customcopy of environ
 *@history: history
 *@alias: alias
 *@isenv_on: if environ changed?? on : off
 *@status: the return status
 *@arg_buffer: address of pointer
 *@cbuffer_type: CMD_type
 *@readfdes: the fd
 *@histcount: the history count
 */
typedef struct customdata
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_coden;
	int lc_flag;
	char *fname;
	dash_t *env;
	dash_t *history;
	dash_t *alias;
	char **environ;
	int isenv_on;
	int status;
	char **arg_buffer;
	int cbuffer_type;
	int readfdes;
	int histcount;
} unistruct_t;

#define INIT_LIST \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(unistruct_t *);
} builtint_t;
extern char **environ;

int dash_loop(unistruct_t *, char **);
int is_builtin(unistruct_t *);
void search_command(unistruct_t *);
void new_fork(unistruct_t *);
int dash_is_cmd(unistruct_t *, char *);
char *duplicat_c(char *, int, int);
char *search_path(unistruct_t *, char *, char *);
int loophsh(char **);
void print_errorstr(char *);
int write_errc(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *comp_ndle(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **split_line(char *, char *);
char *_memset(char *, char, unsigned int);
void dash_ffree(char **);
void *dash_realloc(void *, unsigned int, unsigned int);
int dash_free(void **);
int interactive_mode(unistruct_t *);
int _checkdelim(char, char *);
int _check_c(int);
int _atoi(char *);
int convert_atoi(char *);
void print_error(unistruct_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
int dash_exit(unistruct_t *);
int dash_cd(unistruct_t *);
ssize_t get_input(unistruct_t *);
int _getline(unistruct_t *, char **, size_t *);
void sigintHandler(int);
void reset_unistruct(unistruct_t *);
void init_unistruct(unistruct_t *, char **);
int _setenv(unistruct_t *, char *, char *);
int dash_unsetenv(unistruct_t *);
char *openhist_file(unistruct_t *data);
int fetch_hist(unistruct_t *data);
int write_to_hist(unistruct_t *data);
int loadenviron_list(unistruct_t *);
char **get_environ(unistruct_t *);
int _unsetenv(unistruct_t *, char *);
int append_hist_file(unistruct_t *data, char *buf, int linecount);
int renumber_history(unistruct_t *data);
ssize_t get_node_index(dash_t *, dash_t *);
int dash_logic(unistruct_t *, char *, size_t *);
void cont_add(unistruct_t *, char *, size_t *, size_t, size_t);
int dash_setalias(unistruct_t *);
void free_data(unistruct_t *, int);
char *_getenv(unistruct_t *, const char *);
int dash_env(unistruct_t *);
int dash_setenv(unistruct_t *);
dash_t *add_node(dash_t **, const char *, int);
dash_t *node_comp_ndle(dash_t *, char *, char);
int var_replcmnt(unistruct_t *);
int replace_string(char **, char *);
dash_t *add_node_end(dash_t **, const char *, int);
size_t print_list_str(const dash_t *);
int delete_node_at_index(dash_t **, unsigned int);
void free_list(dash_t **);
size_t list_len(const dash_t *);
char **dash_to_strings(dash_t *);
size_t print_list(const dash_t *);

#endif /* SHELL_H*/
