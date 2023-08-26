#include "pshell.h"

/**
 * execut_cmd - executes command based on arguments passed
 * @cmd_var: struct of command variables
 * Return: status
 */

int execut_cmd(cmd_t cmd_var)
{
	pid_t child;
	char *_command;
	int st;

	_command = _which(cmd_var.cmd[0]);

	if (_command == NULL)
	{
		printMsg(cmd_var.cmd_no, cmd_var.prg_name, cmd_var.cmd[0],
				"not found\n");
		cmd_var.status = 127;
		return (1);
	}
	else
	{
		child = fork();
		if (child == -1)
		{
			perror("Child process failed\n");
			return (1);
		}
		if (child == 0)
		{
			st = execve(_command, cmd_var.cmd, cmd_var.env);
			if (st == -1)
			{
				printMsg(cmd_var.cmd_no, cmd_var.prg_name, cmd_var.cmd[0],
				strerror(errno));
			}
		}
		else
		{
			wait(&cmd_var.status);
			if (_command != cmd_var.cmd[0])
				free(_command);
		}
	}
	return (WEXITSTATUS(cmd_var.status));
}

/**
 * non_interactive - runs in the non interactive mode
 * @buffer: buffer storing the characters read in a line stream
 * @n: number of bytes read
 * @file: a file to be read from
 * @cmd_var: command variables
 * Return: status
 */

int non_interactive(char **buffer, size_t *n, FILE *file, cmd_t cmd_var)
{
	int status = 0;

	while (getline(buffer, n, file) != -1)
	{
		if (_strlen(*buffer) <= 1 || _strspn(*buffer, " \t\n")
				== (size_t)_strlen(*buffer) || *(buffer[0]) == '#')
			continue;
		cmd_var.cmd = tokenize(*buffer, DELIMITER);
		if (cmd_var.cmd == NULL)
		{
			perror("tokenize failed");
			exit(1);
		}
		cmd_var.cmd_no += 1;
		status = execute(cmd_var);
		cmd_var.status = status;
	}
	free(*buffer);
	return (status);
}
