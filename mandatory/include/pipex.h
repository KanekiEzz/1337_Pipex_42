/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:42:20 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/09 11:55:36 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include <stdio.h>

typedef struct s_stract
{
	char	*infile;
	int		fdin;
	char	*outfile;
	int		fdout;
}	t_list;

//	src/pipex.c
void	close_files(t_list *data);

//	components/pipex_utils.c
void	pipex(t_list data, char **av, char **env);

//	find_command.c
char	*find_command_path(char *cmd, char **env);

//	components/error_handling.c
void	error_and_exit(char *str, int exit);
void	close_fd(int fd, char *msg);
void	ft_free_string(char **str);

//	lib/
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtok(char *str, const char *delim);

#endif