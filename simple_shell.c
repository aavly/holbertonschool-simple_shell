
#include "main.h"

/*
 * execute - forks and executes process
 * @arguments: arguments to execute
 * @env: environment variables of system
 */
void execute(char **arguments, char **env)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execve(arguments[0], arguments, env) == -1)
			perror(arguments[0]);
		exit(1);
	}
	else
		wait(NULL);
}

/**
 * main - main function
 * @argc: argument count
 * @argv: argument vector
 * @env: environment variables of system
 * Return: Always 0.
 */
int main(int argc, char *argv[], char **env)
{
	char **arguments;
	char *command;

	/* unused variables */
	(void)argc;
	(void)argv;

	while (1)
	{
		/* in interactive move */
		if (isatty(0))
			printf("#cisfun$ ");

		arguments = get_user_input();
		if (arguments[0] == NULL)
		{
			free(arguments);
			continue;
		}

		command = search_path(arguments[0], env);
		if (command == NULL)
			perror(arguments[0]);
		else
			execute(arguments, env);

		free(arguments);
	}

	return (0);
}

