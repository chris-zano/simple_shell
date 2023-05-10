#ifndef SHELL_H
#define SHELL_H

/* Headerfiles */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Macros used by the shell program */
#define MAX_ARGS 128

/* A group of structures used in the project */
struct command {
    int argc;
    char *argv[MAX_ARGS];
    enum builtin_t {
        NONE, QUIT, JOBS, BG, FG
    } builtin;
};

/* function prototypes used in the program */
void eval(char *);
void runSystemCommand(struct command *, int bg);
int parse(const char *, struct command *);

#endif