# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

// #define MSGSIZE 16 

// char* msg1 = "hello, world #1"; 
// char* msg2 = "hello, world #2"; 
// char* msg3 = "hello, world #3"; 

// int main (int ac, char **av)
// {
// 	int		fd[2];
// 	char	inbuf[MSGSIZE];
// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(1);
// 	}
//     write(fd[1], msg1, MSGSIZE); 
//     write(fd[1], msg2, MSGSIZE); 
//     write(fd[1], msg3, MSGSIZE);
// 	int i = 0;
// 	while (i < 3)
// 	{
// 		read(fd[0], inbuf, MSGSIZE);
// 		printf("-%s\n", inbuf);
// 		i++;
// 	}


// 	close(fd[0]);
// 	close(fd[1]);
// }


// int main()
// {
//     int fd = open("file1.txt", O_WRONLY | O_CREAT, 0644);
//     if (fd == -1)
//         return 1;

//     dup2(fd, STDOUT_FILENO);

//     write(STDOUT_FILENO, "This will be written to the file.\n", 33);

//     close(fd);

//     return 0;
// }
