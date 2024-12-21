
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
	char *path;
	size_t length;

	/* +2 for '/' and '\0' */
	length = strlen(dir) + strlen(filename) + 2;
	path = malloc(length);

	if (!path)
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
		/* make new path using a buffer with enough capacity to hold result */
				snprintf(path, 1000, "%s/%s", dir, filename);
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
 * @filename: name of file to search for
 * @env: environment variable PATH
 * Return: path to file
 */

char *search_path(char *filename, char **env)
{
	char *full_path;
	char *dir;
	char *path;
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

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not found\n");
		return (NULL);
	}

	path = strdup(path);

	if (!path)
	{
		perror("strdup");
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
