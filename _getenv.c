#include "pshell.h"

/**
 * _getenv - searches for a variable in the environment variables
 * @var: variable to look for
 * Return: pointer to variable (string)
 */

char *_getenv(char *var)
{
	char *result;
	char **environment = environ;
	int i = 0, len_var = _strlen(var);

	while (1)
	{
		if (environment[i] == NULL)
			break;
		result = _strstr(environment[i], var);
		/* checks if the current string is the variable*/
		if (result != NULL && result[len_var] == '=' && result ==
				environment[i])
			return (result + len_var + 1);
		i++;
	}
	return (NULL);
}

/**
 * _env - prints the environment variables of an environment
 * @command: command to be executed
 * @enVar: environment variables
 * @command_no: command ID
 * Return: returns exit_status
 */

int _env(char **enVar, int command_no, char *command)
{
	int i = 0;

	(void)command_no;

	while (enVar[i])
	{
		write(STDOUT_FILENO, enVar[i], _strlen(enVar[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}

	if (command == NULL)
		return (2);
	return (0);
}
