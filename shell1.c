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

	while (1)
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
		argv[0] = stkn;

		i = 1;
		while (stkn != NULL)
		{
			stkn = strtok(NULL, " \n");
			argv[i] = stkn;
			i++;
		}
		argv[i] = NULL;

		if (strcmp(argv[0], "exit") == 0 && (argv[1] == NULL))
		{
			free(command);
			free(argv);
			exit(0);
		}

		my_pid = fork();
		{
			if (my_pid == -1)
			{
				perror("Error");
				return (1);
			}

			else if (my_pid == 0)
			{
				printf("the command you entered is %s\n", argv[0]);
				if (execve(argv[0], argv, NULL) == -1)
				{
					perror(argv[0]);
					return (1);
				}
			}
			else
			{
				wait(&status);
			}
			free(argv);
		}
	}
	return (0);
}
