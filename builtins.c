#include "pshell.h"

/**
 * _cd - function to change current working directory
 * @cmd_info: strcut of command varibles
 * Return: status
 */

void _cd(cmd_t cmd_info)
{
	int st;
	char *dir_name = cmd_info.command[1];
	char buff[1024];

	if (dir_name == NULL)
		dir_name = _getenv("HOME");
	else
	{
		if (_strcmp(cmd_info.command[1], "-") == 0)
		{
			dir_name = _getenv("OLDPWD");
			setenv("OLDPWD", (const char *)getcwd(buff, 1024), 1);
			write(STDOUT_FILENO, dir_name, _strlen(dir_name));
			write(STDOUT_FILENO, "\n", 1);
		}
		st = chdir((const char *)dir_name);
		return;
	}
	st = chdir((const char *)dir_name);
	/* checks for permissions or existence of directory */
	if (st == -1)
	{
		dprintf(STDERR_FILENO, "%s: %d: cd: can't cd to %s\n",
		cmd_info.program_name, cmd_info.cmd_no, dir_name);
		cmd_info.status = errno;
		return;
	}
	setenv("PWD", dir_name, 1);
	cmd_info.status = errno;
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
 * @cmd_info: struct of command variables
 * Return: Nothing
 */

void m_exit(cmd_t cmd_info)
{
	char error_msg[] = "Illegal number: ";
	int exit_status = cmd_info.status;

	if (cmd_info.command[1] != NULL)
	{
		/* converts string argument to integer status*/
		if (is_number(cmd_info.command[1]))
		{
			exit_status = _atoi(cmd_info.command[1]);
			if (exit_status < 0)
			{
				printMsg(cmd_info, error_msg);
				_puts(cmd_info.command[1], STDERR_FILENO);
				_puts("\n", STDERR_FILENO);
				exit(2);
			}
			else
			{
				free_grid(cmd_info.command);
				exit(exit_status);
			}
		}
		else
		{
			printMsg(cmd_info, error_msg);
			_puts(cmd_info.command[1], STDERR_FILENO);
			_puts("\n", STDERR_FILENO);
			exit(2);
		}
	}
	free_grid(cmd_info.command);
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
