#include "main.h"

/*
 * search_dir - searches directory for command
 * @filename: name of file command is based on
 * @dir: directory to search command
 * Return: path to file if found, otherwise NULL
 */
char *search_dir(char *filename, char *dir)
{
	DIR *d;
	struct dirent *entry;
	char *path;

	path = malloc(1000);

	if (!path)
	{
		perror("malloc");
		return (NULL);;
	}

	d = opendir(dir);
	if (d)
	{
		while ((entry = readdir(d)) != NULL)
		{
			if (strcmp(entry->d_name, filename) == 0)
			{
		/* make new path using a buffer with enough capacity to hold result */
				snprintf(path, 1000, "%s/%s", dir , filename);
				closedir(d);
				return (path);
			}
		}
		closedir(d);
	}

	free(path);

	return (NULL);
}

/**
 * search_path - search for a file inside PATH
 * @filename:
 * @env:
 * Return: path to file
 */
char *search_path(char *filename, char **env)
{
	char *path;
	char *full_path;
	char *dir;
	int i;

	path = NULL;
	full_path = NULL;
	i = 0;

	while (env[i] != NULL)
	{
		/* if first 5 characters of env[i] and PATH= match */
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			/* this skips the "PATH=" prefix */
			path = env[i] + 5;
			break;
		}
		i++;
	}

	if (!path)
	{
		fprintf(stderr, "Error: PATH environment variable not found\n");
		return (NULL);
	}

	dir = strtok(path, ":");
	while (dir != NULL)
	{
		full_path = search_dir(filename, dir);
		if (full_path)
			return (full_path);
		dir = strtok(NULL, ":");
	}

	return (NULL);
}
