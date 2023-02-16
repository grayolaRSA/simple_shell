#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 *main -takes arguments and runs functions
 *@argc: number of arguments
 *@argv: string content of arguments
 *Return: always zero
 */

extern char **environ;

int main(int argc, char **argv)
{
	char *command = NULL;
	size_t len = 0;
	char *stkn;
	pid_t my_pid;
	int status, i;

	while (i)
	{
		printf("$ ");
		getline(&command, &len, stdin);

		stkn = strtok(command, " \n");

		char **arr = malloc(sizeof(char *) * 32);

		arr[0] = stkn;

		i = 1;
		while (stkn != NULL)
		{
			stkn = strtok(NULL, " \n");
			arr[i] = stkn;
			i++;
		}

		if (strcmp(arr[0], "exit") == 0 && (arr[1] == NULL))
			exit(0);

		if (strcmp(arr[0], "env") == 0 && (arr[1] == NULL))
		{
			i = 0;
			char environ[] = NULL;
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

	}
	free(command);
	return (0);
}
