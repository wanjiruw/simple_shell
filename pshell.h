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
#include <fcntl.h>
#include "prints.h"

/*Macros*/
#define PROMPT "$ "
#define DELIMITER " \t\n"
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
	int (*cmd)(char **, int);
} built_t;

/*checks for command in the path*/
char *_which(char *);
int execut_cmd(char **, int*, int);

char **tokenize(char *, const char *);
int is_builtin(char *command);
int exec_builtin(char **command, int*, int);

/*Handles allocated memory*/
void free_grid(char **);
char *_strtok(char *, char *);

/* Prototypes for builtin functions*/
int (*get_builtin(char **))(char **, int);
int m_exit(char **, int);
int _cd(char **, int);
int _isdigit(int);

/*string manipulations function Prototypes*/
int _strlen(char *s);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);
char *_strdup(char *);
int print_integer(int num);
int _putchar(char c);
int _puts(char *c, int fd);
unsigned int _strspn(char *s, char *accept);

extern char **environ;
extern int commands_no;
char **standby;
#endif
