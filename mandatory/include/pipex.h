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
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

/* FUNCTIONS */
size_t	ft_strlen(const char *str);
void	error_and_exit(char *str, int exit);







void	execute_cmd(char *av, char **ev);
void	execute_help(char **cmd1, char **ev);
char	**freet(char **ptr, int i);
void	parent(char **av, int *fd, char **ev);
char	*find_path(char **ev, char *vr_env);
char	*ft_strchr(const char *s, int c);
char	*ft_strtok(char *str, char *delimter);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char *s2);
void	child_1(char **av, int *fd, char **ev);
char	**ft_split(char const *s, char c);

#endif