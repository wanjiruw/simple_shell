#include "pshell.h"

/**
 * _which - gets the path of a command
 * @command: a string
 * Return: path to the command
 */

char *_which(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, dir_length;
	struct stat buffer;

	path = _getenv("PATH");
	if (path)
	{
		/*checks if command is exist*/
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		path_copy = strdup(path);

		command_length = _strlen(command);
		/*tokenize path and converts to full pathname*/
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			dir_length = _strlen(path_token);
			file_path = malloc(command_length + dir_length + 2);
			join(file_path, path_token, command, "/");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		return (NULL);
	}
	return (NULL);
}
