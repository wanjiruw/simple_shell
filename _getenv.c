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
 * @cmd_info: bunch of variables
 * Return: returns exit_status
 */

void _env(cmd_t cmd_info)
{
	int i = 0;

	while (cmd_info.env[i])
	{
		write(STDOUT_FILENO, cmd_info.env[i], _strlen(cmd_info.env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	cmd_info.status = 0;

}
