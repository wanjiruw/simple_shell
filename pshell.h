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

/*Macros*/
#define PROMPT "$ "
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

/*checks for command in the path*/
char *_which(char *);
void execut_cmd(char **);

char **tokenize(char *, const char *);

/*Handles allocated memory*/
void free_grid(char **);
char *_strtok(char *, char *);

/* Prototypes for builtin functions*/
void (*get_builtin(char **))(char **);
void m_exit(char **);
void _cd(char **);
int _isdigit(int);

/*string manipulations function Prototypes*/
int _strlen(char *s);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);
char *_strdup(char *);

extern char **environ;
extern int commands_no;
char **standby;
#endif
