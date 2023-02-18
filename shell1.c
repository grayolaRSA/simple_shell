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


int main(void)
{
	char *command = NULL;
	size_t len = 0;
	char *stkn;
	pid_t my_pid;
	int status, i = 1;
	char **argv;
	ssize_t read;

	while (i)
	{
		printf("$ ");
		read = getline(&command, &len, stdin);
		argv = (char **)malloc(sizeof(char *) * (read + 1));
		if (argv == NULL)
		{
			perror("malloc");
			exit(1);
		}

		stkn = strtok(command, " \n");
		i = 0;
		while (stkn != NULL)
		{
			argv[i] = stkn;
			i++;
			stkn = strtok(NULL, "\n");
		}
		argv[i] = NULL;

		if (strcmp(argv[0], "exit") == 0 && (argv[1] == NULL))
		{
			free(command);
			free(argv);
			exit(0);
		}

	}

	my_pid = fork();
	{
		if (my_pid == 0)
		{
			printf("the command you entered is %s", argv[0]);
			if (execvp(argv[0], argv) == -1)
			{
				perror(argv[0]);
				return (1);
			}
		}
		else
		{
			wait(&status);
			free(argv);
		}

		if (my_pid == -1)
		{
			perror("Error");
			return (1);
		}
	}
	return (0);
}
