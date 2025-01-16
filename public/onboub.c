#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		perror("Pipe creation failed");
		exit(1);
	}
	pid_t Pid = fork();
	if (Pid == -1)
	{
		perror("Fork faild");
		exit(1);
	}
	if (Pid == 0)
	{
		close(fd[0]);
		char message[] = "Hello from the child process\n";
		write(fd[1], message, sizeof(message));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		char buffer[100];
		read(fd[0], buffer, sizeof(buffer));
		printf("Parent received: %s", buffer);
		close(fd[0]);
	}
	return 0;
}