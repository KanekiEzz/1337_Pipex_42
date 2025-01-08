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