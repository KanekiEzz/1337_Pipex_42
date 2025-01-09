/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:49:38 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/09 11:57:14 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	error_and_exit(char *str, int exite)
{
	if (exite == -9)
	{
		write(2, str, ft_strlen(str));
		exit (1);
	}
	perror(str);
	if (exite != 0)
		exit(exite);
}

void	close_fd(int fd, const char *msg)
{
	if (close(fd) == -1)
		error_and_exit(msg, 1);
}
