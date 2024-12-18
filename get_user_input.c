#include "main.h"

/**
 * get_user_input - uses getline to accept user input
 * Return: user input
 */
char **get_user_input()
{
	char *buffer = NULL;
	size_t n = 0;
	char *token;
	char **arguments = malloc(sizeof(char *) * 32);
	int i = 0;

	if (getline(&buffer, &n, stdin) == -1)
	{
		free(buffer);
		/* exit on CTRL+D */
		exit(0);
	}

	buffer[strlen(buffer) - 1] = '\0';

	token = strtok(buffer, " ");
	while (token != NULL)
	{
		arguments[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	arguments[i] = NULL;
	free(buffer);

	return (arguments);
}
