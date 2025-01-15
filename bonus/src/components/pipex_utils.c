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

void	redirect_fd(int from_fd, int to_fd, const char *str)
{
	if (dup2(from_fd, to_fd) == -1)
		error_and_exit((char *)str, 1);
	close(from_fd);
}

void	execute_cmd(char *cmd, char **env)
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

void	close_all_pipe(int **pipes, int num_cmd)
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

void	free_all_pipe(int **pipes, int i)
{
	while (--i >= 0)
		free(pipes[i]);
	free(pipes);
}

void	pipex(t_list data, char **av, char **env)
{
	int		**pipes;
	int		i;
	int		num_cmds;

	i = 0;
	num_cmds = data.num_cmds;
	pipes = malloc(sizeof(int *) * (num_cmds - 1));
	if (!pipes)
		error_and_exit("Pipe allocation failed\n", 1);
	while (i < num_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
			(free_all_pipe(pipes, i),
				error_and_exit("Pipe creation failed\n", 1));
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
