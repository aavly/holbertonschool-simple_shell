#include "main.h"

/**
 * search_dir - searches directory for command
 * @filename: name of file command is based on
 * @dir: directory to search command
 * Return: path to file if found, otherwise NULL
 */
char *search_dir(char *filename, char *dir)
{
	DIR *d;
	struct dirent *entry;
<<<<<<< HEAD
	char *path;

	path = malloc(strlen(dir) + strlen(filename) + 2);
	if (!path)
=======
	char *full_path = malloc(sizeof(char *));

	if (full_path == NULL)
>>>>>>> refs/remotes/origin/main
	{
		perror("malloc");
		return (NULL);
	}

	d = opendir(dir);
	if (d)
	{
		while ((entry = readdir(d)) != NULL)
		{
			if (strcmp(entry->d_name, filename) == 0)
			{
<<<<<<< HEAD
		/* make new path using a buffer with enough capacity to hold result */
				snprintf(path, strlen(dir) + strlen(filename),
				"%s/%s", dir, filename);
=======
				/* make new path using a buffer with enough capacity to hold result */
				snprintf(full_path, strlen(dir) + strlen(filename) + 2, "%s/%s", dir, filename);
>>>>>>> refs/remotes/origin/main
				closedir(d);
				return (full_path);
			}
		}
		closedir(d);
	}
<<<<<<< HEAD
	free(path);
=======

	free(full_path);
>>>>>>> refs/remotes/origin/main
	return (NULL);
}

/**
 * get_path_variable - gets PATH variable from enviornment
 * @env: environment
 * Return: PATH variable
 */
char *get_path_variable(char **env)
{
	char *path;
	int i = 0;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			/* this skips the "PATH=" pref */
			path = strdup(env[i] + 5);

			if (path == NULL)
			{
				perror("strdup");
				return (NULL);
			}

			return (path);
		}
		i++;
	}

	return (NULL);
}

/**
 * search_path - search for a file inside PATH
 * @filename: name of file to search for
 * @env: environment variable PATH
 * Return: path to file
 */
char *search_path(char *filename, char **env)
{
	char *full_path = NULL;
	char *dir;
	char *path;

	path = get_path_variable(env);

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not found\n");
		return (NULL);
	}

	dir = strtok(path, ":");
	while (dir != NULL)
	{
		full_path = search_dir(filename, dir);
		if (full_path)
		{
			free(path);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}
