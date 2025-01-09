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

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void redirect_fd(int from_fd, int to_fd, const char *msg)
{
    if (dup2(from_fd, to_fd) == -1)
        error_and_exit(msg, 1);
    close_fd(from_fd, "close");
}

void child_2(char **av, int *fd, char **ev)
{
    int outfile;

    close_fd(fd[1], "close");

    outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfile == -1)
        error_and_exit(av[4], 1);

    redirect_fd(outfile, 1, "dup2");
    close_fd(outfile, "close");

    redirect_fd(fd[0], 0, "dup2");

    execute_cmd(av[3], ev);
}

void child_1(char **av, int *fd, char **ev)
{
    int infile;

    close_fd(fd[0], "close");

    infile = open(av[1], O_RDONLY);
    if (infile == -1)
        error_and_exit(av[1], 127);

    redirect_fd(infile, 0, "dup2");
    close_fd(infile, "close");

    redirect_fd(fd[1], 1, "dup2");

    execute_cmd(av[2], ev);
}
