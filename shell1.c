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


int main(int argc, char *argv[])
{
	char *command = NULL;
	size_t len = 0;
	char *stkn;
	pid_t my_pid;
	int status, i = 1;
	char **args;


	while (i)
	{
		printf("$ ");
		getline(&command, &len, stdin);

		stkn = strtok(command, " \n");
		args = malloc(sizeof(char *) * argc);
		args[0] = stkn;

		i = 1;
		while (stkn != NULL)
		{
			stkn = strtok(NULL, " \n");
			argv[i] = stkn;
			i++;
		}

		if (strcmp(args[0], "exit") == 0 && (args[1] == NULL))
			free(command);
		free(args);
		exit(0);
	}

	my_pid = fork();
	{
		if (my_pid == -1)
		{
			perror("Error");
			return (1);
		}
		else
			if (my_pid == 0)
			{
				args = malloc(sizeof(char *) * argc);
				if (execve(args[0], args, NULL) == -1)
				{
					perror(args[0]);
					return (1);
				}

			}
			else
			{
				wait(&status);
			}
		free(args);
	}
	return (0);
}
