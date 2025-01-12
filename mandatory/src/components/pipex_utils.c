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

void	pipex(t_list data, char **av, char **env)
{
	int	end[2];

	if (pipe(end) == -1)
		error_and_exit("pipe error...\n", 14);
	child1(data, av[2], end, env);
	close(data.fdin);
	child2(data, av[3], end, env);
	close(data.fdout);
	close(end[0]);
	close(end[1]);
	while (wait(NULL) != -1)
		;
}
