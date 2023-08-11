#include "pshell.h"

/**
 * tokenize - tokenizes a stream of characters
 * @str: string to tokenize
 * @delim: delimiter
 * Return: array to tokens
 */

char **tokenize(char *str, const char *delim)
{
	char **words, *cpy, *token;
	int i = 0, num_tokens = 0;

	cpy = malloc(sizeof(char) * strlen(str) + 1);
	if (cpy == NULL)
		return (NULL);
	strcpy(cpy, str);
	token = strtok(str, delim);

	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	num_tokens++;
	words = malloc(sizeof(char *) * num_tokens);
	if (words == NULL)
		return (NULL);
	token = strtok(cpy, delim);
	while (token != NULL)
	{
		words[i] = malloc(sizeof(char) * strlen(token) + 1);
		strcpy(words[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	words[i] = NULL;
	free(cpy);
	return (words);
}
