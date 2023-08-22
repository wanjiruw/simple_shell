#include "pshell.h"

/**
 * execut_cmd - executes command based on arguments passed
 * @full_command: an array of strings(command) to be executed
 * @program_name: program name
 * @command_no: command id or number for erro msg
 * Return: status
 */

int execut_cmd(char **full_command, char *program_name, int command_no)
{
	pid_t child;
	char *_command;
	int st, status = 0;

	if (full_command != NULL)
	{
		_command = _which(full_command[0]);

		if (_command == NULL)
		{
			printMsg(command_no, program_name);
			_puts(full_command[0], STDERR_FILENO);
			_puts(": not found\n", STDERR_FILENO);
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
				st = execve(_command, full_command, environ);
				if (st == -1)
				{
					printMsg(command_no, program_name);
					_puts(strerror(errno), STDERR_FILENO);
					write(STDERR_FILENO, "\n", 1);
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
