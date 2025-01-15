/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:44:42 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/09 11:44:42 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

static	void	handel_no_hirdoc(int ac, char **av, char **env)
{
	t_list data;

	data.infile = av[1];
	data.fdin = open(av[1], O_RDONLY, 0466);
	if (data.fdin == -1)
		(write(2, "error open no such file or directory\n", 37),
				write(2, av[1], ft_strlen(av[1])),
						write(2, "\n", 1), data.fdin = STDERR_FILENO);
	data.outfile = av[ac - 1];
	data.fdout = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.fdout == -1)
		(close(data.fdin), error_and_exit("Error opening output file\n", 1));
	data.num_cmds = ac - 3;
	pipex(data, av, env);
	if (data.fdin >= 0)
		close(data.fdin);
	if (data.fdout >= 0)
		close(data.fdout);
}

int	main(int ac, char **av, char **env)
{
	t_list	data;

	if (ac < 5)
		error_and_exit("USAGE: ./pipex infile cmd1 cmd2 ... outfile\n", 1);
	if (!env)
		error_and_exit("Environment variables not found\n", 1);
	if (ac >= 5 && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
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
