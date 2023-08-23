#include "pshell.h"

/**
 * execut_cmd - executes command based on arguments passed
 * @full_command: an array of strings(command) to be executed
 * @program_name: program name
 * @command_no: command id or number for erro msg
 * @envp: environment variable
 * Return: status
 */

int execut_cmd(char **full_command, char *program_name, int command_no, char **envp)
{
	pid_t child;
	char *_command;
	int st, status = 0;

	if (full_command != NULL)
	{
		_command = _which(full_command[0]);

		if (_command == NULL)
		{
			printMsg(command_no, program_name, full_command[0],
					"not found\n");
			return (127);
		}
		else
		{
			child = fork();
			if (child == -1)
			{
				perror("Child process failed\n");
				return (errno);
			}
			if (child == 0)
			{
				st = execve(_command, full_command, envp);
				if (st == -1)
				{
					printMsg(command_no, program_name, full_command[0], strerror(errno));
				}
			}
			else
			{
				wait(&status);
				if (_command != full_command[0])
					free(_command);
			}
		}
	}
	return (WEXITSTATUS(status));
}

/**
 * non_interactive - runs in the non interactive mode
 * @buffer: buffer storing the characters read in a line stream
 * @n: number of bytes read
 * @file: a file to be read from
 * @program_name: program name
 * @envp: environment variables
 * Return: status
 */

int non_interactive(char **buffer, size_t *n, FILE *file, char *program_name, char **envp)
{
	int status = 0, command_no = 0;
	char **argv;

	while (getline(buffer, n, file) != -1)
	{
		if (_strlen(*buffer) <= 1 || _strspn(*buffer, " \t\n")
				== (size_t)_strlen(*buffer))
			continue;
		argv = tokenize(*buffer, DELIMITER);
		if (argv == NULL)
		{
			perror("tokenize failed");
			exit(1);
		}
		command_no++;
		status = execute(argv, program_name, command_no, envp);
	}
	return (status);
}
