
<h1 align="center">1337🇲🇦_Pipex_Tutorial_🇬🇧 - 42 Kaneki</h1>
<p align="center">
  <a href="https://github.com/KanekiEzz/1337_Pipex_42">
    <img src="https://raw.githubusercontent.com/KanekiEzz/kaneki_badges/refs/heads/main/pipexm.png" alt="42 Badge">
  </a>
</p>


## Overview

The **Pipex** project is an implementation of a simplified shell pipeline functionality in C. It reproduces the behavior of the Unix pipe `|`, allowing the execution of multiple commands where the output of one command is passed as the input to the next.

This project also includes a **bonus part**, extending its functionality to handle additional features such as `here_doc` and multiple commands.

---

## Features

### Mandatory Part

- Executes a pipeline between two commands (e.g., `cmd1 | cmd2`).
- Handles file redirection for input and output.
- Proper error handling for invalid commands, files, and system calls.
- Supports:
  - `dup2` for file descriptor duplication.
  - `fork` for process creation.
  - `pipe` for inter-process communication.
  - `execve` to replace process images.

### Bonus Part

- Handles multiple commands (e.g., `cmd1 | cmd2 | cmd3 | ... | cmdN`).
- Implements `here_doc` functionality for heredoc input redirection.
- Additional utilities for flexible pipeline construction.

---

## Explanation

💡 **The number of times ‘hello’ is printed** is equal to the number of processes created. 

🎯 **Total Number of Processes** = `2^n`, where `n` is the number of fork system calls. So here `n = 3`: 
`2^3 = 8`.  

Let us put some label names for the three lines:

```c
fork ();   // Line 1
fork ();   // Line 2
fork ();   // Line 3
```

Visualization:
```
       L1       // There will be 1 child process 
    /     \     // created by line 1.
  L2      L2    // There will be 2 child processes
 /  \    /  \   // created by line 2
L3  L3  L3  L3  // There will be 4 child processes 
                // created by line 3
```

---

## Directory Structure

```
pipex/
|-- bonus/
|   |-- pipex_bonus.c
|   |-- src/
|   |   |-- components/
|   |   |   |-- creat_child_bonus.c
|   |   |   |-- error_handling_bonus.c
|   |   |   |-- find_command_path_bonus.c
|   |   |   |-- her_doc_bonus.c
|   |   |   |-- pipex_utils_bonus.c
|   |   |-- lib/
|   |       |-- ft_split_bonus.c
|   |       |-- ft_strdup_bonus.c
|   |       |-- ft_strjoin_bonus.c
|   |       |-- ft_strlen_bonus.c
|   |       |-- ft_strncmp_bonus.c
|   |       |-- ft_strtok_bonus.c
|   |-- get_next_line/
|       |-- get_next_line_bonus.c
|       |-- get_next_line_utils_bonus.c
|-- src/
|   |-- pipex.c
|   |-- components/
|       |-- creat_child.c
|       |-- error_handling.c
|       |-- find_command_path.c
|       |-- pipex_utils.c
|-- lib/
|   |-- ft_split.c
|   |-- ft_strdup.c
|   |-- ft_strjoin.c
|   |-- ft_strlen.c
|   |-- ft_strncmp.c
|   |-- ft_strtok.c
|-- get_next_line/
|   |-- get_next_line.c
|   |-- get_next_line_utils.c
|-- Makefile
|-- README.md
```

---

## Compilation and Execution

### Build the Project

Run the following command to compile the project:

```bash
make
```

To compile the bonus version:

```bash
make bonus
```

### Clean Up

To remove all object files and executables:

```bash
make clean
```

To also remove bonus object files:

```bash
make fclean
```

### Execute the Program

Run the program like this:

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

This command is equivalent to:

```bash
< input.txt grep hello | wc -l > output.txt
```

---

## Pipe Details

```c
int pipe(int fds[2]);
```

Parameters:

- `fd[0]` will be the file descriptor for the **read end** of the pipe.
- `fd[1]` will be the file descriptor for the **write end** of the pipe.

**Returns:**
- `0` on success.
- `-1` on error.

---

## Advanced Examples

### Run with Environment Isolation:

```bash
env -i bash
```

### Example Commands:

```bash
./pipexl /dev/stdin "echo hello" "echo hello" /dev/stdout
```

```bash
./pipexl /dev/stdin pwd pwd /dev/stdout
```

```bash
./pipexl /dev/stdin ls /bin/pwd /dev/stdout
```

```bash
valgrind ./pipexl Makefile cat "cat Makefile" cat ls "/bin/ls -la" /bin/ls/cat /dev/stdout
```

```bash
< /dev/stdin ff | ../../../../../../usr/bin/ls | cat Makefile > /dev/stdout
```

```bash
./pipex_bonus /dev/stdin "ff" "../../../../../../usr/bin/ls" "cat Makefile" /dev/stdout
```

#### Result:

```bash
command not found: ls
/home/iezzam/kaneki/1337_Pipex_42
```

---

## Debugging Commands

🛠️ Use these for debugging:

```bash
ps aux | grep pipex
lsof -p number

while true; do lsof -p 527654; sleep 1; clear; done
```

---

## Examples with PATH Reset

remove path => 
```bash
env -i PATH= 
```
```bash
./pipex_bonus /dev/stdin "cat" "ls" /dev/stdout
```
```bash
./pipex_bonus /dev/stdin "/bin/cat" "/bin/ls" /dev/stdout
```
### Command-Pipe Relationships:

For 4 commands (i.e., cmd1, cmd2, cmd3, cmd4):

🎯 **You need 3 pipes.**
- Pipe 1: connects cmd1 to cmd2.
- Pipe 2: connects cmd2 to cmd3.
- Pipe 3: connects cmd3 to cmd4.

Thus, you will need to open 3 pipes for 4 commands.

---


# 👨‍💻 Author ✍🏼

<table>
  <tr>
    <td align="center"><a href="https://github.com/KanekiEzz/"><img src="https://avatars.githubusercontent.com/u/110631781?s=400&u=0cd1de60c073f367d291df9c6ccef5c18ac64e41&v=4" width="100px;" alt="100px"/><br /><sub><b>iezzam</b></sub></a><br /><a href="https://profile.intra.42.fr/users/iezzam" title="Intra 42">iezzam42</a></td>
  </tr>
</table>


# 🔍 You might be interested!

### 📚  - To see my progress in the common core 42 ↙️

[HERE](https://github.com/KanekiEzz/42cursus)

### 👤 - My profile on the intra 42 ↙️

[HERE](https://profile.intra.42.fr/users/iezzam)