#include "pshell.h"

/**
 * _cd - function to change current working directory
 * @cmd_var: command variables
 * Return: status
 */

int _cd(cmd_t cmd_var)
{
	int status = 0;
	int st;
	char *dir_name = cmd_var.cmd[1];
	char buff[1024];

	if (dir_name == NULL)
		dir_name = _getenv("HOME");
	else
	{
		/*TO BE BACK*/
		if (_strcmp(dir_name, "-") == 0)
		{
			dir_name = _getenv("OLDPWD");
			setenv("OLDPWD", (const char *)getcwd(buff, 1024), 1);
			write(STDOUT_FILENO, dir_name, _strlen(dir_name));
			write(STDOUT_FILENO, "\n", 1);
		}
		st = chdir((const char *)dir_name);
	}
	st = chdir((const char *)dir_name);
	/* checks for permissions or existence of directory */
	if (st == -1)
	{
		dprintf(STDERR_FILENO, "%s: %d: cd: can't cd to %s\n",
				cmd_var.prg_name, cmd_var.cmd_no, dir_name);
		cmd_var.status = errno;
		status = errno;
		return (status);
	}
	setenv("PWD", dir_name, 1);
	return (status);
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
 * @cmd_var: command variables
 * Return: status
 */

int m_exit(cmd_t cmd_var)
{
	char error_msg[] = "Illegal number: ";
	int exit_status = cmd_var.status;

	if (cmd_var.cmd[1] != NULL)
	{
		/* converts string argument to integer status*/
		if (is_number(cmd_var.cmd[1]))
		{
			exit_status = _atoi(cmd_var.cmd[1]);
			if (exit_status < 0)
			{
				printMsg(cmd_var.cmd_no, cmd_var.prg_name, cmd_var.cmd[0], error_msg);
				_puts(cmd_var.cmd[1], STDERR_FILENO);
				_puts("\n", STDERR_FILENO);
				return (2);
			}
			else
			{
				free_grid(cmd_var.cmd);
				exit(exit_status);
			}
		}
		else
		{
			printMsg(cmd_var.cmd_no, cmd_var.prg_name, cmd_var.cmd[0], error_msg);
			_puts(cmd_var.cmd[1], STDERR_FILENO);
			_puts("\n", STDERR_FILENO);
			return (2);
		}
	}
	free_grid(cmd_var.cmd);
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
