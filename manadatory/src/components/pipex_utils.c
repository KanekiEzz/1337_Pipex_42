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

void	child_2(char **av, int *fd, char **ev)
{
	int		outfile;

	if (close(fd[1]) == -1)
		error_and_exit("close", 1);
	outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
		error_and_exit(av[4], 1);
	if (dup2(outfile, 1) == -1)
		error_and_exit("dup2", 1);
	if (close(outfile) == -1)
		error_and_exit("close", 1);
	if (dup2(fd[0], 0) == -1)
		error_and_exit("dup2", 1);
	if (close(fd[0]) == -1)
		error_and_exit("close", 1);
	execute_cmd(av[3], ev);
}

void	child_1(char **av, int *fd, char **ev)
{
	int		infile;

	if (close(fd[0]) == -1)
		error_and_exit("close", 1);
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		error_and_exit(av[1], 127);
	if (dup2(infile, 0) == -1)
		error_and_exit("dup2", 1);
	if (close(infile) == -1)
		error_and_exit("close", 1);
	if (dup2(fd[1], 1) == -1)
		error_and_exit("dup2", 1);
	if (close(fd[1]) == -1)
		error_and_exit("close", 1);
	execute_cmd(av[2], ev);
}