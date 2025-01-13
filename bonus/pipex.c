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

void handle_here_doc(char *limiter, int *fd)
{
    char *line;
    size_t len = 0;

    // Create a pipe
    if (pipe(fd) == -1)
        error_and_exit("Pipe creation failed for here_doc\n", 1);

    while (1)
    {
        write(1, "heredoc> ", 9);
        if (getline(&line, &len, stdin) == -1)
            break;

        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
            break;

        write(fd[1], line, ft_strlen(line));
    }

    free(line);
    close(fd[1]);
}

int	main(int ac, char **av, char **env)
{
	t_list	data;
	int		*fd;

	if (ac < 5)
		error_and_exit("USAGE: ./pipex infile cmd1 cmd2 ... outfile\n", 1);
	if (!env)
		error_and_exit("Environment variables not found\n", 1);
	if (ac >= 5 && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		data.infile = av[2];
		data.fdin = 0;
		data.outfile = av[ac - 1];
		data.fdout = open(data.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data.fdout == -1)
            error_and_exit("Error opening output file\n", 1);
        data.num_cmds = ac - 3;

        fd = malloc(sizeof(int) * 2);
        handle_here_doc(av[2], fd);

        pipex(data, av, env);

        close(data.fdout);
        close(fd[0]);
        free(fd);
	}
	if (ac >= 5)
	{
		data.infile = av[1];
		data.fdin = open(av[1], O_RDONLY, 0466);
		if (data.fdin == -1)
            (write(2, "Error opening infile: ", 22), write(2, av[1], ft_strlen(av[1])), write(2, "\n", 1), data.fdin = STDERR_FILENO);
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
	return (0);
}
