/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:52:10 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/16 17:37:42 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	child2(t_list data, char *cmd, int *end, char **env)
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

void	child1(t_list data, char *cmd, int *end, char **env)
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
		printf("===i: %d\tid: %d\n", i, pid);
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
		close(pipes[i - 1][1]);
		close(pipes[i - 1][0]);
		i++;
	}
}
