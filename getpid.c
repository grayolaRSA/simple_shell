#include <stdio.h>
#include <unistd.h>

/**
 *get_pid - gets maximum pid value in a function
 *Return: nothing
 */

int get_pid(void)
{
printf("The maximum PID value is: %d\n", getpid());
return (0);
}
