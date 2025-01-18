/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:52:10 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/18 10:23:10 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"
void	close_files(t_list *data)
{
	if (data->fdin >= 0)
		close(data->fdin);
	if (data->fdout >= 0)
		close(data->fdout);
}
void	child2(t_list data, char *cmd, int *wr_pipe, char **env)
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

void	child1(t_list data, char *cmd, int *wr_pipe, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(wr_pipe[0]);
		redirect_fd(data.fdin, 0, "dup2 failed\n");
		redirect_fd(wr_pipe[1], 1, "dup2 failed\n");
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

void	child_intermediate(t_list data, char **av, int **pipes, char **env)
{
	int		num_cmds;
	int		i;
	pid_t	pid;

	i = 1;
	num_cmds = data.num_cmds;
	while (i < num_cmds - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			close(pipes[i - 1][1]);
			redirect_fd(pipes[i - 1][0], 0, "dup2 failed\n");
			close(pipes[i][0]);
			redirect_fd(pipes[i][1], 1, "dup2 failed\n");
			close_all_pipe(pipes, num_cmds);
			execute_cmd(av[i + 2], env);
		}
		else if (pid == -1)
		{
			close_files(&data);
			error_and_exit("fork failed\n", 1);
		}
		close(pipes[i - 1][1]);
		close(pipes[i - 1][0]);
		i++;
	}
	close(pipes[num_cmds - 2][0]);
    close(pipes[num_cmds - 2][1]);

}

