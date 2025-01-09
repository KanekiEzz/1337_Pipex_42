# Calculate the number of times hello is printed.
```
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    fork();
    fork();
    fork();
    printf("hello\n");
    return 0;
}
```
Explanation

The number of times ‘hello’ is printed is equal to the number of processes created. Total Number of Processes = 2n,
where n is the number of fork system calls. So here n = 3, 23 = 8 Let us put some label names for the three lines:

fork ();   // Line 1
fork ();   // Line 2
fork ();   // Line 3
       L1       // There will be 1 child process 
    /     \     // created by line 1.
  L2      L2    // There will be 2 child processes
 /  \    /  \   //  created by line 2
L3  L3  L3  L3  // There will be 4 child processes 
                // created by line 3


# Execution
Run the program like this:
```
./pipex input.txt "grep hello" "wc -l" output.txt
```

This command is equivalent to:
```
< input.txt grep hello | wc -l > output.txt
```



```
int pipe(int fds[2]);
```

Parameters :
```fd[0] will be the fd(file descriptor) for the 
read end of pipe.
fd[1] will be the fd for the write end of pipe.
Returns : 0 on Success.
-1 on error.```