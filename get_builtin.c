#include "pshell.h"

/**
 * get_builtin - get specific builint function
 * @b_cmd: builtin command
 * Return: function pointer to specific function else NULL
 */

int (*get_builtin(char **b_cmd))(cmd_t cmd_var)
{
	int i = 0;

	/* an array of function points */
	built_t ops[] = {
		{"cd", _cd},
		{"exit", m_exit},
		{"env", _env}
	};

	while (i < 3)
	{
		if (strcmp(b_cmd[0], ops[i].cmd_n) == 0)
		{
			return (ops[i].cmd);
		}
		i++;
	}
	return (NULL);
}
