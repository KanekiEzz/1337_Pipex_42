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
	write(2, "command not found: ", 19);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(1);
}

static	void	child2(t_list data, char *cmd, int *wr_pipe, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(wr_pipe[1]);
		redirect_fd(wr_pipe[0], 0, "dup2 failed\n");
		redirect_fd(data.fdout, 1, "dup2 failed\n");
		execute_cmd(cmd, env);
	}
	else if (pid == -1)
	{
		close(wr_pipe[0]);
		close(wr_pipe[1]);
		close_files(&data);
		error_and_exit("fork failed\n", 1);
	}
}

static	void	child1(t_list data, char *cmd, int *wr_pipe, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(wr_pipe[0]);
		redirect_fd(data.fdin, 0, 0);
		redirect_fd(wr_pipe[1], 1, 0);
		execute_cmd(cmd, env);
	}
	else if (pid == -1)
	{
		close(wr_pipe[0]);
		close(wr_pipe[1]);
		close_files(&data);
		error_and_exit("fork failed\n", 1);
	}
}

void	pipex(t_list data, char **av, char **env)
{
	int		wr_pipe[2];
	t_list	file;

	if (pipe(wr_pipe) == -1)
		(close_files(&data),
			error_and_exit("pipe error...\n", 1));
	child1(data, av[2], wr_pipe, env);
	close(data.fdin);
	child2(data, av[3], wr_pipe, env);
	close(data.fdout);
	close(wr_pipe[0]);
	close(wr_pipe[1]);
	while (wait(NULL) != -1)
		;
}
