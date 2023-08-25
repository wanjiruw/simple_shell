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

/*Macros*/
#define PROMPT "$ "
#define DELIMITER " \n"

/**
 * struct command_var - this is a struct for command variables
 * @program_name: executable name
 * @cmd_no: command number or ID
 * @status: programs status
 * @env: environment variables
 */

typedef struct command_var
{
	char *program_name;
	int cmd_no;
	int status;
	char **command;
	char **env;
} cmd_t;

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
	void (*cmd)(cmd_t);
} built_t;

#include "prints.h"
extern char **environ;
/*checks for command in the path*/
char *_which(char *);
void execut_cmd(cmd_t cmd_info);

char **tokenize(char *, const char *);
int is_builtin(char *command);
void exec_builtin(cmd_t cmd_info);

/*Handles allocated memory*/
void free_grid(char **);
char *_strtok(char *, char *);

/* Prototypes for builtin functions*/
void (*get_builtin(char **))(cmd_t cmd_info);
void m_exit(cmd_t cmd_info);
void _cd(cmd_t cmd_info);
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
void _env(cmd_t);
int _setenv(const char *, const char *, int);
int non_interactive(char **buffer, size_t *n, FILE *file, cmd_t);
void execute(cmd_t);
#endif
