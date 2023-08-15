#include "pshell.h"

/**
 * _cd - function to change current working directory
 * @dir_name: dir name or dir path name
 * Return: status
 */

void _cd(char **dir_name)
{
	int st;

/*	if (dirname[1] == NULL)
		st = chdir*/
	st = chdir((const char *)dir_name[1]);
	/* checks for permissions or existence of directory */
	if (st != 0)
	{
		dprintf(STDERR_FILENO, "hs: %d: cd: can't cd to %s\n",
				commands_no, dir_name[1]);
	}
}

/**
 * is_number - checks a string if it contains a non-int character
 * @string: string to check
 * Return: 1 if true, 0 otherwise
 */

int is_number(char *string)
{
	while (*string)
	{
		if (_isdigit(*string) == 0)
			return (0);
		string++;
	}
	return (1);
}

/**
 * m_exit - terminates a process
 * @command: command entered at CLI
 * Return: Nothing
 */

void m_exit(char **command)
{

	if (_strcmp(command[0], "exit") == 0)
	{
		if (command[1] != NULL)
		{
			/* converts string argument to integer status*/
			if (is_number(command[1]))
			{
				free_grid(command);
				exit(atoi(command[1]));

			}
			else
			{
				perror("illegal number");
				return;
			}
		}
		free_grid(command);
		exit(0);
	}
}
/**
 * _isdigit - checks for digit 0-9
 * @c: int character
 * Return: 1 if c is a digit else 0
 */

int _isdigit(int c)
{
	int result;

	if (c >= 48 && c < 58)
		result = 1;
	else
		result = 0;
	return (result);
}
