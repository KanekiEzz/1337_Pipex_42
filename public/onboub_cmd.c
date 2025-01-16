#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
	pid_t pid1, pid2;

	pid1 = fork();
	if (pid1 = 0)
	{
		char *args1 = {"sleep", "5", NULL};
		execve("/bin/sleep", args1, NULL);
		perror("Execve failed for child 1");
		exit(1);
	}
	else if (pid1 < 0)
		perror("fork faild for child 1");

	pid_t pid1, pid2;

	pid1 = fork();
	if (pid1 = 0)
	{
		char *args1 = {"sleep", "3", NULL};
		execve("/bin/sleep", args1, NULL);
		perror("Execve failed for child 1");
		exit(1);
	}
	else if (pid1 < 0)
		perror("fork faild for child 1");

	wait(NULL);
	wait(NULL);

	return 0;
}