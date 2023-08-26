#include "pshell.h"

/**
 * execute - starts execution based command type
 * @cmd_var: command variables
 * Return: Nothing
 */

int execute(cmd_t cmd_var)
{
	int status = 0; /**DON'T FORGET TO COME BACK*/

	if (is_builtin(cmd_var.cmd[0]))
		status = exec_builtin(cmd_var);
	else
		status = execut_cmd(cmd_var);
	free_grid(cmd_var.cmd);
	return (status);
}

/**
 * exec_builtin - executes buitlin command
 * @cmd_var: command variables
 * Return: void
 */

int exec_builtin(cmd_t cmd_var)
{
	int status = 0;
	int (*built_command)(cmd_t cmd_var);

	built_command = get_builtin(cmd_var.cmd);
	if (built_command == NULL)
	{
		perror("builtin failed");
		cmd_var.status = 127;
		return (127);
	}
	else
		status = built_command(cmd_var);
	return (status);
}


/**
 * is_builtin - checks if command is a builtin command
 * @command: first token of command passed
 * Return: 1 if command is a built and 0 if otherwise
 */

int is_builtin(char *command)
{
	char *builtins[] = {"cd", "exit", "env", NULL};
	int i = 0;

	for (; builtins[i] != NULL; i++)
	{
		if (_strcmp(command, builtins[i]) == 0)
			return (1);
	}
	return (0);
}

/**
 * _prompt - prompts user for commands
 * @cmd_var: command variables
 * Return: 0
 */
int _prompt(cmd_t cmd_var)
{
	char *command = NULL;
	size_t n = 0;
	ssize_t characters_read;
	int status = 0;

	/* Create a loop for the shell's prompt */
	while (1)
	{
		write(STDOUT_FILENO, PROMPT, 2);
		characters_read = getline(&command, &n, stdin);
		/* check if the getline function failed or reached EOF or user use CTRL + D*/
		if (characters_read == -1)
		{
			break;
		}
		if (_strlen(command) <= 1 || _strspn(command, " \t\n")
				== (size_t)_strlen(command) || command[0] == '#')
			continue;
		/*Tokenize command*/
		cmd_var.cmd = tokenize(command, DELIMITER);
		/* execute the command */
		cmd_var.cmd_no += 1;
		status = execute(cmd_var);
	}
	free(command);
	return (status);
}

/**
 * main - entry point
 * @ac: number of command line arguments
 * @argv: array of arguments
 * @envp: environment variable
 * Return: 0 on success otherwise failure status
 */

int main(int ac, char **argv, char **envp)
{
	cmd_t cmd_var = {0};
	char *buffer = NULL;
	size_t n = 0;
	FILE *stream = stdin;

	cmd_var.prg_name = argv[0];
	cmd_var.env = envp;
	/*checks interactiveness.*/
	if (isatty(STDIN_FILENO))
	{
		if (ac == 2)
		{
			int accs = access(argv[1], R_OK);

			stream = fopen(argv[1], "r");
			if (accs != -1 && stream != NULL)
			{
				cmd_var.status = non_interactive(&buffer, &n, stream, cmd_var);
				fclose(stream);
			}
			else
			{
				dprintf(STDERR_FILENO, "%s: 0: Can't open %s\n",
				cmd_var.prg_name, argv[1]);
				return (127);
			}
		}
		else
			cmd_var.status = _prompt(cmd_var);
	}
	/*checks non-interactive*/
	else
	{
		cmd_var.status = non_interactive(&buffer, &n, stream, cmd_var);
	}
	return (cmd_var.status);
}
