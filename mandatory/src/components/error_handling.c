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
	write(2, str, ft_strlen(str));
	exit (exite);
}

void	close_fd(int fd, char *str)
{
	if (close(fd) == -1)
		error_and_exit(str, 1);
}
