/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:40:26 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/19 17:40:31 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_stract
{
	char	*infile;
	char	*outfile;
	int		fdin;
	int		fdout;
	int		num_cmds;
}	t_list;

void	pipex(t_list data, char **av, char **env);
void	pipex_herdoc(t_list data, char **av, char **env);
void	redirect_fd(int from_fd, int to_fd, const char *str);
void	execute_cmd(char *cmd, char **env);
void	close_all_pipe(int **pipes, int num_cmd);
void	free_all_pipe(int **pipes, int i);
char	*find_command_path(char *cmd, char **env);
void	error_and_exit(char *str, int exit);
void	close_fd(int fd, char *msg);
void	ft_free_string(char **str);
void	child2(t_list data, char *cmd, int **wr_pipe, char **env);
void	child1(t_list data, char *cmd, int **wr_pipe, char **env);
void	child_intermediate(t_list data, char **av, int **pipes, char **env);
void	handle_here_doc(char *limiter, int *fd);
// void	pipex_herdoc(t_list data, char **av, char **env);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtok(char *str, const char *delim);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int search);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
