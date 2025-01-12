
#include "../mandatory/include/pipex.h"

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

// enum Level {
// 	Low = 25,
// 	MEDIUM = 50,
// 	High = 75
// };

// int main ()
// {

// 	printf("%d", Low);
// }

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int main(int ac, char **av, char **env)
// {
//     (void)ac;
//     (void)av;

//     char *path = getenv("PATH");
//     if (!path)
//     {
//         fprintf(stderr, "PATH environment variable not found.\n");
//         return 1;
//     }

//     char path_copy[4096];
//     strncpy(path_copy, path, sizeof(path_copy) - 1);
//     path_copy[sizeof(path_copy) - 1] = '\0';

//     const char delim[2] = ":";
//     char *token;

//     token = strtok(path_copy, delim);

//     while (token != NULL)
//     {
//         printf("%s\n", token);
//         token = strtok(NULL, delim);
//     }

//     return 0;
// }



// int main(int ac, char **av, char **env)
// {
// 	if (ac == 2)
// 	{
// 		int i = 0;
// 		char **c = ft_split(av[1], ' ');
//     	char *envp[] = { NULL };
// 		if (execvp(c[0], c) == -1)
// 			perror("execve");
// 	}
//     return 0;
// }


// int main(int ac, char **av, char **env) {
//     if (ac < 2) {
//         fprintf(stderr, "Usage: %s <command>\n", av[0]);
//         return 1;
//     }

//     char *cmd = av[1];
//     char *path = getenv("PATH");
//     char full_cmd[1024];
//     int found = 0;

//     if (path) {
//         char *dir = strtok(path, ":");
//         while (dir) {
//             snprintf(full_cmd, sizeof(full_cmd), "%s/%s", dir, cmd);
//             if (access(full_cmd, X_OK) == 0) {
//                 found = 1;
//                 printf("===cmd: %s\n==\n", full_cmd);
//                 break;
//             }
//             dir = strtok(NULL, ":");
//         }
//     }

//     if (!found) {
//         printf("ta (lwa)\n");
//     }

//     return 0;
// }


//	use dup
// int main ()
// {
// 	int file_desc = open("dup.txt", O_WRONLY | O_APPEND);

// 	if (file_desc < 0)
// 		printf("error \n");
// 	int copy_desc = dup(file_desc);

// 	write(copy_desc,"This will be output to the file named dup.txt\n", 46); 
	
// 	write(file_desc,"This will also be output to the file named dup.txt\n", 51); 
// 	printf("file 1: %d\n", file_desc);
// 	printf("file 1: %d\n", copy_desc);
// }


//	use dup2
// int main ()
// {
// 	int file_desc = open("tricky.txt", O_WRONLY | O_APPEND);
// 	int file_hi = open("dup.txt", O_WRONLY | O_APPEND);
// 	int i = dup2(file_desc, 0);
// 	if (i == -1)
// 	{
// 		perror("error");
// 		return 1;
// 	}
// 	printf("I will be printed in the file tricky.txt\n");
// 	printf("tricky.txt: %d\n", file_desc);
// 	printf("tricky.txt: %d\n", file_hi);
// 	printf("i: %d\n", i);
// }


//	execve
// int main (int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)env;

// 	printf("Main Program started\n");
// 	char *argv1[] = {"ls" , NULL};
// 	char *envp[] = {"PATH=/bin:/usr/bin", NULL};

// 	if (execve("ls", argv1, env) == -1)
// 		perror("Cloud not execve");
// 	return 1;
// }

//	---------access-------------

// #include <string.h>

// char	*ft_strdup(const char *str)
// {
// 	size_t	i;
// 	char	*ptr;
// 	size_t	len;

// 	len = (strlen(str) + 1);
// 	ptr = malloc(len * sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		ptr[i] = str[i];
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

// int main(int ac, char **av, char **env)
// {
// 	int i = 0;
//     // const char *file = "/usr/bin/ls";
    
// 	// if (access(file, X_OK) == -1)
// 	// 	perror("File does not exist or cannot be accessed");
// 	// printf("%s", env[3]);
// 	while (env[i] && strncmp(env[i], "PATH=", 5) != 0)
// 		i++;
// 	char *path = ft_strdup(env[i] + 5);
// 	printf("%s\n", path);
// 	char *dir = strtok(path, ":");
// 	while (dir)
// 	{
// 		printf("=> %s\n", dir);
// 		dir = strtok(NULL, ":");
// 	}
// 	return 0;
// }