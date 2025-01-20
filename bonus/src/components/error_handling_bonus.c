/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:46:40 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/19 17:46:40 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	ft_free_string(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	return ;
}

void	error_and_exit(char *str, int exite)
{
	write(2, str, ft_strlen(str));
	exit (exite);
}

void	close_fd(int fd, char *str)
{
	if (close(fd) == -1)
		error_and_exit(str, 1);
}
