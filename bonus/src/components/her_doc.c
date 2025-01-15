/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:50:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/15 17:00:46 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	handle_here_doc(char *limiter, int *fd)
{
	char	*line;

    if (pipe(fd) == -1)
        error_and_exit("Pipe creation failed for here_doc\n", 1);
    while (1)
    {
        write(1, "here_doc> ", 10);
        line = get_next_line(0);

        if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break;
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
    }
    close(fd[1]);
}


void pipex_herdoc(t_list data, char **av, char **env)
{
    int heredoc_pipe[2];
    int cmd_pipe[2];

    handle_here_doc(av[2], heredoc_pipe);

    if (pipe(cmd_pipe) == -1)
        error_and_exit("Pipe creation failed\n", 1);

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        close(heredoc_pipe[1]);
        redirect_fd(heredoc_pipe[0], 0, "Error redirecting heredoc input\n");
        redirect_fd(cmd_pipe[1], 1, "Error redirecting output\n");
        close(cmd_pipe[0]);
        execute_cmd(av[3], env);
    }

    close(heredoc_pipe[0]);
    close(cmd_pipe[1]);
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        redirect_fd(cmd_pipe[0], 0, "Error redirecting input\n");
        redirect_fd(data.fdout, 1, "Error redirecting output\n");
        execute_cmd(av[4], env);
    }
    close(cmd_pipe[0]);
    close(data.fdout);
    while (wait(NULL) != -1)
        ;
}
