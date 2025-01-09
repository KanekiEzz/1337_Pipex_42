# include <unistd.h>
# include <stdio.h>

int main (int ac, char **av)
{
	int		fd[2];
	// if (ac != 5)
		// printf("USAGE: ./pipex infile cmd1 cmd2 outfile\n");
	// if (pipe(fd) == -1)
		// printf("pipe");
	int i = pipe(fd);

	prinf("pipe: %d", i);
}