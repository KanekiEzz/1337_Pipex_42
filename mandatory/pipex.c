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

int	main(int ac, char **av, char **ev)
{
	int		fd[2];
	int		id;
	int		id2;

	if (ac != 5)
		error_and_exit("USAGE: ./pipex infile cmd1 cmd2 outfile\n", -9);
	if (pipe(fd) == -1)
		error_and_exit("pipe", 1);
	id = fork();
	if (id == -1)
		error_and_exit("fork", 1);
	if (id == 0)
		child_1(av, fd, ev);
	// id2 = fork();
	// if (id2 == -1)
	// 	error_and_exit("fork", 1);
	// if (id2 == 0)
	// 	child_2(av, fd, ev);
	// if (close(fd[0]) == -1 || close(fd[1]) == -1)
	// 	error_and_exit("close", 1);
	// if (waitpid(id, NULL, 0) == -1)
	// 	error_and_exit("waitpid 1st child", 1);
	// if (waitpid(id2, NULL, 0) == -1)
	// 	error_and_exit("waitpid 2ed child", 1);
	// return (0);
}

