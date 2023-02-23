#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 *main -takes arguments and runs functions
 *Return: void
 */

extern char **environ;

int main(void)
{
	char *command = NULL;
	size_t len = 0;
	char *stkn;
	pid_t my_pid;
	int status, i;
	ssize_t read;
	char **arr;
	char *environ[];

	while (1)
	{
		printf("$ ");
		read = getline(&command, &len, stdin);

		stkn = strtok(command, " \n");

		arr = malloc(sizeof(char *) * (read + 1));

		arr[0] = stkn;

		i = 1;
		while (stkn != NULL)
		{
			stkn = strtok(NULL, " \n");
			arr[i] = stkn;
			i++;
		}
		arr[i] = NULL;

		if (strcmp(arr[0], "exit") == 0 && (arr[1] == NULL))
		{
			free(command);
			free(arr);
			exit(0);
		}

		if (strcmp(arr[0], "env") == 0 && (arr[1] == NULL))
		{
			i = 0;
			while (environ[i] != NULL)
			{
				printf("%s\n", environ[i]);
				i++;
			}
			continue;
		}
		my_pid = fork();
		if (my_pid == -1)
		{
			perror("Error");
			return (1);
		}

		else
			if (my_pid == 0)
			{
				if (execve(arr[0], arr, NULL) == -1)
				{
					perror(arr[0]);
					return (1);
				}

			}
			else
			{
				wait(&status);
			}
		free(arr);
	}
	return (0);
}
