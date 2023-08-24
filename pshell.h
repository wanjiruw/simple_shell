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
#define DELIMITER " \n"
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
	int (*cmd)(char **, int, char *);
} built_t;

extern char **environ;
/*checks for command in the path*/
char *_which(char *);
int execut_cmd(char **, char *, int, char **);

char **tokenize(char *, const char *);
int is_builtin(char *command);
int exec_builtin(char **command, char *, int, char **);

/*Handles allocated memory*/
void free_grid(char **);
char *_strtok(char *, char *);

/* Prototypes for builtin functions*/
int (*get_builtin(char **))(char **, int, char *);
int m_exit(char **, int, char *);
int _cd(char **, int, char *);
int _isdigit(int);
int _atoi(char *str);

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
char *_strstr(char *haystack, char *needle);
void join(char *, char *, char *, const char *);

/*Environment Functions*/
char *_getenv(char *var);
int _env(char **, int, char *);
int _setenv(const char *, const char *, int);
int non_interactive(char **buffer, size_t *n, FILE *file, char *, char **);
int execute(char **command, char *program_name, int command_no, char **);
#endif
