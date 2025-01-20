/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:45:18 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/19 17:45:18 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex_bonus.h"

static	void	close_files(t_list *data)
{
	close(data->fdin);
	close(data->fdout);
}

void	open_files(t_list *data, int ac, char **av)
{
	data->infile = av[1];
	data->fdin = open(av[1], O_RDONLY, 0644);
	if (data->fdin == -1)
	{
		write(2, "error open no such file or directory: ", 38);
		write(2, av[1], ft_strlen(av[1]));
		write(2, "\n", 1);
		data->fdin = STDERR_FILENO;
	}
	data->outfile = av[ac - 1];
	data->fdout = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fdout == -1)
	{
		close_files(data);
		error_and_exit("Error opening output file\n", 1);
	}
}

static	void	handel_no_hirdoc(int ac, char **av, char **env)
{
	t_list	data;

	open_files(&data, ac, av);
	data.num_cmds = ac - 3;
	pipex(data, av, env);
	close_files(&data);
}

int	main(int ac, char **av, char **env)
{
	t_list	data;

	if (ac < 5)
		error_and_exit("USAGE: ./pipex_bonus infile cmd1 cmd2 ... outfile\n", 1);
	if (!env)
		error_and_exit("Environment variables not found\n", 1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac != 6)
			error_and_exit("USAGE:\n\
				./pipex_bonus here_doc limiter cmd1 cmd2 outfile\n", 1);
		data.outfile = av[ac - 1];
		data.fdout = open(data.outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (data.fdout == -1)
			error_and_exit("Error opening output file\n", 1);
		pipex_herdoc(data, av, env);
		close(data.fdout);
	}
	else if (ac >= 5)
		handel_no_hirdoc(ac, av, env);
	return (0);
}
