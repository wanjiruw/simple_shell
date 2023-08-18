#include "pshell.h"

/**
 * _cd - function to change current working directory
 * @dir_name: dir name or dir path name
 * Return: status
 */

int _cd(char **dir_name, int command_no)
{
	int st;

	st = chdir((const char *)dir_name[1]);
	/* checks for permissions or existence of directory */
	if (st == -1)
	{
		dprintf(STDERR_FILENO, "hs: %d: cd: can't cd to %s\n",
				command_no, dir_name[1]);
	}
	return (errno);
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

int m_exit(char **command, int command_no)
{
	char error_msg[] = "illegal number\n";
	int exit_status = 0;

	if (command[1] != NULL)
	{
		/* converts string argument to integer status*/
		if (is_number(command[1]))
		{
			exit_status = atoi(command[1]);
			if (exit_status < 0)
			{
				printMsg(command_no);
				write(STDERR_FILENO, error_msg, _strlen(error_msg));
				exit_status = 2;
				return (exit_status);
			}
			else
			{
				free_grid(command);
				exit(exit_status);
			}
		}
		else
		{
			printMsg(command_no);
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
			exit_status = 2;
			return (exit_status);
		}
	}
	free_grid(command);
	exit(exit_status);
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
