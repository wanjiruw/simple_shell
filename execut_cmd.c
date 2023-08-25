#include "pshell.h"

/**
 * execut_cmd - executes command based on arguments passed
 * @cmd_info: struct of variables
 * Return: status
 */

void execut_cmd(cmd_t cmd_info)
{
	pid_t child;
	char *_command;
	int st, status = 0;

	if (cmd_info.command != NULL)
	{
		_command = _which(cmd_info.command[0]);

		if (_command == NULL)
		{
			printMsg(cmd_info, "not found\n");
			cmd_info.status = 127;
			return;
		}
		else
		{
			child = fork();
			if (child == -1)
			{
				perror("Child process failed\n");
				return;
			}
			if (child == 0)
			{
				st = execve(_command, cmd_info.command, cmd_info.env);
				if (st == -1)
				{
					printMsg(cmd_info, strerror(errno));
					return;
				}
			}
			else
			{
				wait(&status);
				if (_command != cmd_info.command[0])
					free(_command);
			}
		}
	}
	cmd_info.status = WEXITSTATUS(status);
}

/**
 * non_interactive - runs in the non interactive mode
 * @buffer: buffer storing the characters read in a line stream
 * @n: number of bytes read
 * @file: a file to be read from
 * @cmd_info: a struct of command varibles
 * Return: status
 */

int non_interactive(char **buffer, size_t *n, FILE *file, cmd_t cmd_info)
{
	int status = 0;
	char **argv;

	while (getline(buffer, n, file) != -1)
	{
		if (_strlen(*buffer) <= 1 || _strspn(*buffer, " \t\n")
				== (size_t)_strlen(*buffer) || *(buffer[0]) == '#')
			continue;
		argv = tokenize(*buffer, DELIMITER);
		if (argv == NULL)
		{
			perror("tokenize failed");
			exit(1);
		}
		cmd_info.cmd_no += 1;
		execute(cmd_info);
	}
	free(*buffer);
	return (status);
}
