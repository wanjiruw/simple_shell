#include "pshell.h"

int commands_no = 0;
/**
 * exec_builtin - executes buitlin command
 * @command: function pointer to execute command
 * Return: void
 */

void exec_builtin(char **command)
{
	void (*built_command)(char **);

	built_command = get_builtin(command);
	if (built_command == NULL)
	{
		commands_no++;
		perror("builtin failed");
		return;
	}
	commands_no++;
	built_command(command);
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
 * Return: 0
 */
int _prompt(char **argv)
{
	char *command = NULL;
	size_t n = 0;
	ssize_t characters_read;
	const char *delim = " \n";

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
		/*Tokenize command*/
		argv = tokenize(command, delim);
		/* execute the command */
		if (argv != NULL)
		{
			if (is_builtin(argv[0]))
				exec_builtin(argv);
			else
				execut_cmd(argv);
			free_grid(argv);
		}
	}
	free(command);
	return (0);
}

/**
 * main - entry point
 * @ac: number of command line arguments
 * @argv: array of arguments
 * Return: 0 on success
 */

int main(int ac, char **argv)
{
	char buffer[1024];
	memset(buffer, 0, 1024);
	ssize_t fd;
	(void)ac;
	/*checks interactiveness.*/
	if (isatty(STDIN_FILENO))
	{
		_prompt(argv);
	}
	else
	{
		fd = read(STDIN_FILENO, buffer, 1024);
		if (fd == -1)
		{
			perror("Error!");
		}
		argv = tokenize(buffer, " \n");
		if (argv == NULL)
		{
			perror("Error!");
		}
		execut_cmd(argv);
	}
	exit(0);
}
