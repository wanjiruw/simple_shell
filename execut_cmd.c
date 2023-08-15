#include "pshell.h"

/**
 * execut_cmd - executes command based on arguments passed
 * @full_command: an array of strings(command) to be executed
 */

void execut_cmd(char **full_command)
{
	pid_t child;
	char *_command;

	_command = _which(full_command[0]);

	if (full_command != NULL)
	{
		if (_command == NULL)
			dprintf(STDERR_FILENO, "sh: 1: %s: not found\n", _command);
		else
		{
			child = fork();
			if (child == -1)
				return;
			if (child == 0)
			{
				if (execve(_command, full_command, environ) == -1)
					perror("Error: execve failed");
			}
			wait(&child);
			if (_command != full_command[0])
				free(_command);
		}
	}
}
