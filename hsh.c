#include "pshell.h"

/**
 * execute - starts execution based command type
 * @cmd_info: struct of variables
 * Return: Nothing
 */

void execute(cmd_t cmd_info)
{

	if (cmd_info.command != NULL)
	{
		if (is_builtin(cmd_info.command[0]))
			exec_builtin(cmd_info);
		else
			execut_cmd(cmd_info);
		free_grid(cmd_info.command);
	}
}

/**
 * exec_builtin - executes buitlin command
 * @cmd_info: struct of variables
 * Return: void
 */

void exec_builtin(cmd_t cmd_info)
{
	void (*built_command)(cmd_t);

	built_command = get_builtin(cmd_info.command);
	if (built_command == NULL)
	{
		perror("builtin failed");
		cmd_info.status = 127;
		return;
	}
	built_command(cmd_info);
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
 * @cmd_info: struct of command variables
 * Return: NOTHING
 */
void _prompt(cmd_t cmd_info)
{
	char *command = NULL;
	size_t n = 0;
	ssize_t characters_read;

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
		cmd_info.command = tokenize(command, DELIMITER);
		/* execute the command */
		cmd_info.cmd_no += 1;
	}
	free(command);
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
	char *buffer = NULL;
	cmd_t cmd_info = {0};
	size_t n = 0;
	FILE *stream = stdin;

	cmd_info.program_name = argv[0];
	cmd_info.env = envp;
	/*checks interactiveness.*/
	if (isatty(STDIN_FILENO))
	{
		if (ac == 2)
		{
			non_interactive(&buffer, &n, stream, cmd_info);
		}
		else
			_prompt(cmd_info);
	}
	/*checks non-interactive*/
	else
	{
		non_interactive(&buffer, &n, stream, cmd_info);
	}
	return (cmd_info.status);
}
