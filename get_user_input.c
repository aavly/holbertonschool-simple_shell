#include "main.h"

/**
 * get_user_input - uses getline to accept user input
 * Return: user input
 */
char **get_user_input()
{
	char *buffer = NULL;
	size_t n = 0, size = 32;
	char *token;
	char **arguments;
	int i = 0, j = 0;

	arguments = malloc(sizeof(char *) * size);
	if (!arguments)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (getline(&buffer, &n, stdin) == -1)
	{
		free(buffer);
		free(arguments);
		/* exit on CTRL+D */
		exit(0);
	}

	/* removing trailing newline if present */
	if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n')
		buffer[strlen(buffer) - 1] = '\0';

	token = strtok(buffer, " ");
	while (token != NULL)
	{
		if (i >= (int)(size - 1))
		{
			size = size * 2;
			arguments = realloc(arguments, size * sizeof(char *));
			if (!arguments)
			{
				perror("realloc");
				free(buffer);
				exit(EXIT_FAILURE);
			}
		}

		arguments[i] = strdup(token);
		if (!arguments[i])
		{
			perror("strdup");
			free(buffer);
			for (j = 0; j < i; j++)
				free(arguments[j]);
			free(arguments);
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, " ");
		i++;
	}

	arguments[i] = NULL;
	free(buffer);

	return (arguments);
}
