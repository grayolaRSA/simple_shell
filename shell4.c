#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 *tokenizes - tokenizes string input
 *@argc: number of arguments input by user
 *@words: words in string line
 *@delim: delimiting character
 *Return: command line arguments
 */

char **tokenizes(int *argc, char *words, char *delim)
{
	char *token;
	char *cmd_cop;
	char **argv;
	int i = 0;

	cmd_cop = strdup(words);

	*argc = 1;

	token = strtok(words, delim);

	if (token != NULL)
	{
		(*argc)++;

		while ((token = strtok(NULL, delim)) != NULL)
		{
			(*argc)++;
		}
	}

	argv = malloc(sizeof(char *) * (*argc));
	token = strtok(cmd_cop, delim);

	for (i = 0; token; i++)
	{
		argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(argv[i], token);
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	free(cmd_cop);
	return (argv);
}

/**
 *isValidPath - checks if path is valid
 *@path: file path
 *Return: integer
 */

int isValidPath(char *path)
{
	struct stat sb;

	if (stat(path, &sb) == 0)
		return (1);
	return (0);
}

/**
 *getPath - path function
 *@cmd: command line
 *Return: character string
 */

char *getPath(char *cmd)
{
	char *allPath;
	char *token;
	char *fullPath = NULL;

	if (access(cmd, X_OK) != -1)
		return (cmd);
	allPath = getenv("PATH");
	token = strtok(allPath, ":");

	while (token)
	{
		fullPath = malloc((strlen(token) + strlen(cmd) + 2) * sizeof(char));
		strcpy(fullPath, token);
		strcat(fullPath, "/");
		strcat(fullPath, cmd);

		if (access(fullPath, X_OK) != -1)
		{
			return (fullPath);
		}
		if (fullPath != NULL)
		{
			free(fullPath);
			fullPath = NULL;
		}
		token = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 *shellexec - execute by path
 *@args: command line arguments
 *Return: integer
 */

int shellexec(char **args)
{
	pid_t my_pid;
	int status;

	my_pid = fork();
	if (my_pid == -1)
	{
		perror("Error pid");
		exit(EXIT_FAILURE);
	}

	else
		if (my_pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("Unknown command");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
			{
				perror("wait error");
				exit(EXIT_FAILURE);
			}
		}

	if (strcmp(args[0], "exit") == 0 && (args[1] == NULL))
	{
		exit(EXIT_SUCCESS);
	}
	return (0);
}
/**
 *main - combines all function
 *Return: integer
 */

int main(void)
{
	size_t size;
	char *words;
	char *delim;
	char *path = NULL;
	int read, argc = 0;
	char **argv;

	while (1)
	{
		size = 3;
		printf("$ ");
		read = getline(&words, &size, stdin);

		if (read == -1)
		{
			free(words);
			return (-1);
		}
		delim = " \n";
		argv = tokenizes(&argc, words, delim);
		path = getPath(argv[0]);

		while (path != NULL)
		{
			shellexec(argv);
		}
		free(argv);
		free(words);
	}
	return (0);
}
