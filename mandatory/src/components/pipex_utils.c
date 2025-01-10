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
    close_fd(from_fd, "close");
}

static void execute_cmd(char *cmd, char **env)
{
    char **args;
    char *full_path;

    args = ft_split(cmd, ' ');
	if (!args)
        error_and_exit("ft_split failed\n", 1);

    full_path = find_command_path(args[0], env);
	if (!full_path)
        error_and_exit("find_command_path failed\n", 1);

    if (full_path)
    {
        free(args[0]);
        args[0] = full_path;
    }

    execve(args[0], args, env);

	free(args);
    // error_and_exit("execve failed\n", 1);
}

// static void    execute_cmd(char *cmd, char **env)
// {
//     char **args = ft_split(cmd, ' ');
//     if (!args)
//     {
//         perror("ft_split");
//         exit(EXIT_FAILURE);
//     }
//     if (execvp(args[0], args) == -1)
//     {
//         perror("execvp");
//         free(args);
//         exit(EXIT_FAILURE);
//     }
// }


static	void	child2(t_list data, char *cmd, int *end, char **env)
{
    pid_t	pid;

    pid = fork();
    if (pid == 0)
	{
        close(end[1]);
		redirect_fd(end[0], 0, "dup2 failed\n");
		redirect_fd(data.fdout, 1, "dup2 failed\n");
		execute_cmd(cmd, env);
	}
	else if (pid == -1)
	{
		perror(NULL);
	}
}

static	void	child1(t_list data, char *cmd, int *end, char **env)
{
	pid_t pid;

    pid = fork();
    if (pid == 0)
	{
        close(end[0]);
        redirect_fd(data.fdin, 0, "dup2 failed\n");
		redirect_fd(end[1], 1, "dup2 failed\n");
        execute_cmd(cmd, env);
    }
	else if (pid == -1)
	{
        perror(NULL);
    }
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
