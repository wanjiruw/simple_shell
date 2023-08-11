#ifndef PSHELL_H
#define PSHELL_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
extern char **environ;

/* Structures */

/**
 * struct builtin_t - this is a structure of funtion pointers for built
 * builtin commands
 * @cmd_n: command name of type char *
 * @cmd: function pointer
 */

typedef struct builtin_t
{
	char *cmd_n;
	void (*cmd)(char **);
} built_t;

int _cd(char *dir_name);
char *_which(char *);
void execut_cmd(char **);
char **tokenize(char *, const char *);
void free_grid(char **);
#endif
