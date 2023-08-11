#include "pshell.h"

/**
 * is_builtin - checks if command is a builtin command
 * @command: first token of command passed
 * Return: 1 if command is a built and 0 if otherwise
 */

int is_builtin(char *command)
{
	char *builtins[] = {"cd", "env", "exit", NULL};
	int i = 0;

	for (; builtins[i] != NULL; i++)
	{
		if (strcmp(command, builtins[i]) == 0)
			return (1);
	}
	return (0);
}

/**
 * _prompt - prompts user for commands
 * @argv: command line
 * Return: Nothing
 */
void _prompt(char **argv)
{
	char *prompt = "$ ";
	char *command = NULL;
	size_t n = 0, status = 0;
	ssize_t characters_read;
	const char *delim = " \n";

	/* Create a loop for the shell's prompt */
	while (1)
	{
		printf("%s", prompt);
		characters_read = getline(&command, &n, stdin);
		/* check if the getline function failed or reached EOF or user use CTRL + D*/
		if (characters_read == -1)
		{
			printf("Exiting shell....\n");
			break;
		}
		/*Tokenize command*/
		argv = tokenize(command, delim);
		/* execute the command */
		if (strcmp(argv[0], "exit") == 0)
		{
			if (argv[1] != NULL)
			{
				/* converts string argument to integer status*/
				status = atoi(argv[1]);
				free_grid(argv);
				break;
			}
			free_grid(argv);
			break;
		}
		else
			execut_cmd(argv);
		free_grid(argv);
	}
	free(command);
	exit(status);
}

/**
 * main - entry point
 * @ac: number of command line arguments
 * @argv: array of arguments
 * Return: 0 on success
 */

int main(int ac, char **argv)
{
	(void)ac;
	/*checks interactiveness.*/
	if (isatty(STDIN_FILENO))
	{
		printf("INTERACTIVE MODE\n");
		_prompt(argv);
	}
	else
	{
		printf("Non-interractive not yet Handled\n");
	}
	return (0);
}
