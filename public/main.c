#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t wait_for_child(int *stat_loc)
{
	pid_t pid = wait(stat_loc);
	if (pid == -1)
		return (pid_t) -1;
	return pid;
}

int main(int ac, char **av)
{
	int id = fork();
	if (id == -1)
	{
        perror("fork failed");
        return 1;
    }
	int n;
	if (id == 0)
		n = 1;
	else
		n = 6;
	if (n != 0)
	{
		int status;
		dprintf(2, "1 status: %d\n", WEXITSTATUS(status));
		wait_for_child(&status);
		dprintf(2, "===2 status: %d\n", WTERMSIG(status));
	}
	int i;
	for (i = n; i < n + 5; i++)
	{
		dprintf(2, "%d ", i);
		fflush(stdout);
	}
	if (id != 0)
		dprintf(2, "\n");
	// if (id == 0)
	// 	printf("Hello from child process\n");
	// else
	// 	printf("Hello from the main process\n");
	return 0;
}

