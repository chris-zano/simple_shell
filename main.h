#ifndef MAIN_H
#define MAIN_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>


/* macro definitions */
#define BUFFER_SIZE 1024

extern char **environ;

/* structure defintions */

/**
 * struct list_s - node structure for a singly linked list
 * @c: pointer to a string literal (node data)
 * @next: pointer to next node in the list
 */
typedef struct list_s
{
	char *c;
	struct list_s *next;
} list_t;


/* function declarations */

int create_args_list(int argc, char *argv[]);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **_strtok(char *str);
char *search_path(char *filename);
void execute_command(char *path, char **args);
#endif
