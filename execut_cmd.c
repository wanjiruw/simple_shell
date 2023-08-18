#include "pshell.h"

/**
 * execut_cmd - executes command based on arguments passed
 * @full_command: an array of strings(command) to be executed
 * @status: operation status
 * @command_no: command id or number for erro msg
 */

int execut_cmd(char **full_command, int *status, int command_no)
{
	pid_t child;
	char *_command; int st;
	*status = 0;

	if (full_command != NULL)
	{
		_command = _which(full_command[0]);

		if (_command == NULL)
		{
			printMsg(command_no);
			_puts(strerror(errno), STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
			return (errno);
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
					*status = errno;
					printMsg(command_no);
					_puts(strerror(errno), STDERR_FILENO);
					write(STDERR_FILENO, "\n", 1);
				}	
			}
			wait(&child);
			if (_command != full_command[0])
				free(_command);

		}
	}
	return (*status);
}
