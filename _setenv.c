#include "pshell.h"

/**
 * _setenv - appends or overwrites a environment variable
 * @name: variable name
 * @value: variable value
 * @overwrite: overwriting option
 * Return: 0 on success else 1
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	char *variable;
	int len_name = _strlen((char *)name),
	    len_value = _strlen((char *)value), i = 0;

	variable = malloc(sizeof(char) * (len_value + len_name + 2));
	if (variable)
		join(variable, (char *)name, (char *)value, "=");
	else
	{
		free(variable);
		perror("Not enough memory");
		return (1);
	}
	if (_getenv((char *)name) == NULL)
	{

		while (environ[i])
			i++;
		environ[i] = variable;
		return (0);
	}
	else if (overwrite)
	{
		while (environ[i])
		{
			if (_strstr(environ[i], (char *)name) == environ[i])
				environ[i] = variable;
			i++;
		}
	}
	return (0);
}
