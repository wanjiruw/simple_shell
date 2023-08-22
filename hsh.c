#include "pshell.h"

/**
 * execute - starts execution based command type
 * @command: command to execute
 * @command_no: command id
 * @program_name: program name
 * Return: Nothing
 */

int execute(char **command, char *program_name, int command_no)
{
	int status = 0;

	if (command != NULL)
	{
		if (is_builtin(command[0]))
			status = exec_builtin(command, program_name, command_no);
		else
			status = execut_cmd(command, program_name, command_no);
		free_grid(command);
	}
	return (status);
}

/**
 * exec_builtin - executes buitlin command
 * @command: function pointer to execute command
 * @program_name: executable name
 * @command_no: command id
 * Return: void
 */

int exec_builtin(char **command, char *program_name, int command_no)
{
	int status = 0;
	int (*built_command)(char **, int, char*);

	built_command = get_builtin(command);
	if (built_command == NULL)
	{
		perror("builtin failed");
		return (errno);
	}
	if (strcmp(command[0], "env") == 0)
		status = built_command(environ, command_no, command[0]);
	else
		status = built_command(command, command_no, program_name);
	return (status);
}


/**
 * is_builtin - checks if command is a builtin command
 * @command: first token of command passed
 * Return: 1 if command is a built and 0 if otherwise
 */

int is_builtin(char *command)
{
	char *builtins[] = {"cd", "exit", NULL};
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
 * @argv: array of parsed command
 * @commands_no: command id
 * @program_name: program name
 * Return: 0
 */
int _prompt(char **argv, int *commands_no, char *program_name)
{
	char *command = NULL;
	size_t n = 0;
	ssize_t characters_read;
	int status;

	/* Create a loop for the shell's prompt */
	while (1)
	{
		write(STDOUT_FILENO, PROMPT, 2);
		characters_read = getline(&command, &n, stdin);
		/* check if the getline function failed or reached EOF or user use CTRL + D*/
		if (characters_read == -1)
		{
			_puts("\n", STDOUT_FILENO);
			free(command);
			return (status);
		}
		if (_strlen(command) <= 1 || _strspn(command, " \t\n")
				== (size_t)_strlen(command))
			continue;
		/*Tokenize command*/
		argv = tokenize(command, DELIMITER);
		/* execute the command */
		*commands_no = *commands_no + 1;
		status = execute(argv, program_name, *commands_no);
	}
	free(command);
	return (status);
}

/**
 * main - entry point
 * @ac: number of command line arguments
 * @argv: array of arguments
 * Return: 0 on success
 */

int main(int ac, char **argv)
{
	int command_no = 0, status = 0;
	char *buffer = NULL, *program_name = argv[0];
	size_t n = 0;
	(void)ac;
	/*checks interactiveness.*/
	if (isatty(STDIN_FILENO))
	{
		_prompt(argv, &command_no, program_name);
	}
	else
	{
		while (getline(&buffer, &n, stdin) != -1)
		{
			if (_strlen(buffer) <= 1 || _strspn(buffer, " \t\n")
					== (size_t)_strlen(buffer))
				continue;
			argv = tokenize(buffer, DELIMITER);
			if (argv == NULL)
			{
				perror("tokenize failed");
				exit(1);
			}
			command_no++;
			status = execute(argv, program_name, command_no);
		}
	}
	return (status);
}
