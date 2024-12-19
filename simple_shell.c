#include <signal.h>
#include "main.h"

void handle_sigint(int sig)
{
	(void)sig;
	printf("\n#cisfun$ ");
	fflush(stdout);
}

/*
 * execute - forks and executes process
 * @arguments: arguments to execute
 * @env: environment variables of system
 */
void execute(char **arguments, char **env)
{
	char *command;
	int status;
	pid_t pid;

	if (arguments[0] == NULL)
		return;

	if (arguments[0][0] == '/' || arguments[0][0] == '.')
		command = arguments[0];
	else
	{
		command = search_path(arguments[0], env);

		if (command == NULL)
		{
			fprintf(stderr, "%s: Command not found\n", arguments[0]);
			return;
		}
	}

	pid = fork();

	if (pid < 0)
	{
		perror("Error");
	}
	else if (pid == 0)
	{
		execve(command, arguments, env);
		perror("execve");
		free(command);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (arguments[0][0] != '/' && arguments[0][0] != '.')
			free(command);
	}
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
	int i;

	/* unused variables */
	(void)argc;
	(void)argv;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		/* in interactive move */
		if (isatty(0))
			printf("#cisfun$ ");

		arguments = get_user_input();

		if (arguments == NULL)
			break;

		if (strcmp(arguments[0], "exit") == 0)
		{
			for (i = 0; arguments[i]; i++)
				free(arguments[i]);
			free(arguments);
			break;
		}
		execute(arguments, env);

		for (i = 0; arguments[i]; i++)
			free(arguments[i]);
		free(arguments);
	}

	return (0);
}

