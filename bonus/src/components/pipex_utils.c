/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:52:38 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/09 11:53:11 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static	void	redirect_fd(int from_fd, int to_fd, const char *str)
{
	if (dup2(from_fd, to_fd) == -1)
		error_and_exit((char *)str, 1);
    close(from_fd);
}

static	void	execute_cmd(char *cmd, char **env)
{
	char	**args;
	char	*full_path;

	args = ft_split(cmd, ' ');
	if (!args)
		error_and_exit("ft_split failed\n", 1);
	full_path = find_command_path(args[0], env);
	if (!full_path)
	{
		write(2, "command not found: ", 19);
		write(2, args[0], ft_strlen(args[0]));
		write(2, "\n", 1);
		ft_free_string(args);
		free(args);
		exit(1);
	}
	free(args[0]);
	args[0] = full_path;
	execve(args[0], args, env);
	ft_free_string(args);
	free(args);
	error_and_exit("Execution failed\n", 1);
}

static	void	child2(t_list data, char *cmd, int *end, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(end[1]);
		redirect_fd(end[0], 0, 0);
		redirect_fd(data.fdout, 1, 0);
		execute_cmd(cmd, env);
	}
	else if (pid == -1)
		return ;
}

static	void	child1(t_list data, char *cmd, int *end, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		redirect_fd(data.fdin, 0, 0);
		redirect_fd(end[1], 1, 0);
		execute_cmd(cmd, env);
	}
	else if (pid == -1)
		return ;
}

static	void	close_all_pipe(int **pipes, int num_cmd)
{
	int	j;

	if (!pipes)
		return ;
	j = 0;
	while (j < num_cmd - 1)
    {
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

static	void	free_all_pipe(int **pipes, int i)
{
    while (--i >= 0)
        free(pipes[i]);
    free(pipes);
} 

static	void	child_intermediate(t_list data, char **av, int **pipes, char **env)
{
	int num_cmds;
	int	i;

	i = 1;
	num_cmds = data.num_cmds;
	while (i < num_cmds - 1)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            close(pipes[i - 1][1]);
            redirect_fd(pipes[i - 1][0], 0, "Error redirecting input\n");
            redirect_fd(pipes[i][1], 1, "Error redirecting output\n");

			close_all_pipe(pipes, num_cmds);
            execute_cmd(av[i + 2], env);
        }
        else if (pid == -1)
            error_and_exit("fork error...\n", 14);
		i++;
	}
}

#include <string.h>

void handle_here_doc(char *limiter, int *fd)
{
    char *line;

    if (pipe(fd) == -1)
        error_and_exit("Pipe creation failed for here_doc\n", 1);

    while (1)
    {
        write(1, "heredoc> ", 9);
        line = get_next_line(0);
        if (!line)
            break;

        // Strip newline from the line for proper comparison
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';

        // Break if limiter is reached
        if (strcmp(line, limiter) == 0)
        {
            free(line);
            break;
        }

        // Write the line into the pipe
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1); // Restore the newline for heredoc content
        free(line);
    }
    close(fd[1]); // Close write end of the pipe
}

void pipex_herdoc(t_list data, char **av, char **env)
{
    int heredoc_pipe[2];
    int cmd_pipe[2];

    handle_here_doc(av[2], heredoc_pipe);

    if (pipe(cmd_pipe) == -1)
        error_and_exit("Pipe creation failed\n", 1);

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        close(heredoc_pipe[1]);
        redirect_fd(heredoc_pipe[0], 0, "Error redirecting heredoc input\n");
        redirect_fd(cmd_pipe[1], 1, "Error redirecting output\n");
        close(cmd_pipe[0]);
        execute_cmd(av[3], env);
    }

    close(heredoc_pipe[0]);
    close(cmd_pipe[1]);
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        redirect_fd(cmd_pipe[0], 0, "Error redirecting input\n");
        redirect_fd(data.fdout, 1, "Error redirecting output\n");
        execute_cmd(av[4], env);
    }
    close(cmd_pipe[0]);
    close(data.fdout);
    while (wait(NULL) != -1)
        ;
}

void pipex(t_list data, char **av, char **env)
{
    int **pipes;
    int i, num_cmds;

	i = 0;
    num_cmds = data.num_cmds;
    pipes = malloc(sizeof(int *) * (num_cmds - 1));
    if (!pipes)
        error_and_exit("Pipe allocation failed\n", 1);
    while (i < num_cmds - 1)
    {
        pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
            (free_all_pipe(pipes, i), error_and_exit("Pipe creation failed\n", 1));
		i++;
	}
    child1(data, av[2], pipes[0], env);
	child_intermediate(data, av, pipes, env);
    child2(data, av[num_cmds + 1], pipes[num_cmds - 2], env);
    close_all_pipe(pipes, num_cmds);
	free_all_pipe(pipes, num_cmds - 1);
    while (wait(NULL) != -1)
        ;
}
