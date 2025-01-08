#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int id = fork();
	if (id == -1) {
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
		wait(&status);
	}
	int i;
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
	// if (id == 0)
	// 	printf("Hello from child process\n");
	// else
	// 	printf("Hello from the main process\n");
	return 0;
}

