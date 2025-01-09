#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h> // Include for strlen

void error_and_exit(char *str, int exite)
{
    if (exite == -9)
    {
        write(2, str, strlen(str)); // Use standard strlen
        exit(1);
    }
    perror(str);
    if (exite != 0)
        exit(exite);
}

int main(int ac, char **av, char **ev)
{
    int fd[2];
    int id;
    int id2;

    if (ac != 5)
        error_and_exit("USAGE: ./pipex infile cmd1 cmd2 outfile\n", -9);
    return 0;
}
