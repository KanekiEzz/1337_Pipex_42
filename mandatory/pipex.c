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

int	main(int ac, char **av, char **env)
{
	t_list data;

	if (ac != 5)
		error_and_exit("USAGE: ./pipex infile cmd1 cmd2 outfile\n", -9);
	if (!env)
		error_and_exit("USAGE: ./pipex infile cmd1 cmd2 outfile\n", -9);
	if (ac == 5)
	{
		data.infile = av[1];
		data.fdin = open(av[1], O_RDONLY, 0466);
		if (data.fdin)
			error_and_exit("error open\n", 11);
		data.outfile = av[4];
		data.fdout = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data.fdout)
			error_and_exit("error open\n", 11);
		pipex(data, av, env);
		free(data.path);
	}
	return (0);
}
