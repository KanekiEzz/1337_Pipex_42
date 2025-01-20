/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:35:56 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/16 16:26:12 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*_strjoin_save(char **_ptr_li_t_save, char *buffer)
{
	char	*save_ptr_temp;

	if (!*_ptr_li_t_save)
	{
		*_ptr_li_t_save = ft_strdup("");
		if (!*_ptr_li_t_save)
		{
			ft_free((void **)&buffer);
			ft_free((void **)_ptr_li_t_save);
			return (NULL);
		}
	}
	save_ptr_temp = ft_strjoin(*_ptr_li_t_save, buffer);
	if (!save_ptr_temp)
	{
		ft_free((void **)&buffer);
		ft_free((void **)_ptr_li_t_save);
		return (NULL);
	}
	return (save_ptr_temp);
}

static char	*_see_line_(char **_ptr_li_t_save, size_t count, char *backup,
		char *line)
{
	if (!*_ptr_li_t_save)
		return (ft_free((void **)_ptr_li_t_save), NULL);
	while ((*_ptr_li_t_save)[count] && (*_ptr_li_t_save)[count] != '\n')
		count++;
	if ((*_ptr_li_t_save)[count] == '\0')
	{
		line = ft_strdup(*_ptr_li_t_save);
		if (!line)
			return (ft_free((void **)_ptr_li_t_save), NULL);
		ft_free((void **)_ptr_li_t_save);
		return (line);
	}
	line = ft_substr(*_ptr_li_t_save, 0, count + 1);
	if (!line)
		return (ft_free((void **)_ptr_li_t_save), NULL);
	backup = ft_substr(*_ptr_li_t_save, count + 1, ft_strlen(*_ptr_li_t_save)
			- count - 1);
	if (!backup)
		return (ft_free((void **)_ptr_li_t_save), free(line), NULL);
	ft_free((void **)_ptr_li_t_save);
	if (backup && *backup == '\0')
		ft_free((void **)&backup);
	return (*_ptr_li_t_save = backup, line);
}

static char	*_read_fd_line(int fd, char *buffer, char **_ptr_li_t_save,
		int read_line)
{
	size_t	count;
	char	*backup;
	char	*line;
	char	*save_ptr_temp;

	(1) && (count = 0, backup = NULL, line = 0);
	while (1)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line < 0)
			return (ft_free((void **)_ptr_li_t_save), ft_free((void **)&buffer),
				NULL);
		if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		save_ptr_temp = _strjoin_save(_ptr_li_t_save, buffer);
		if (!save_ptr_temp)
			return (ft_free((void **)&buffer), NULL);
		ft_free((void **)_ptr_li_t_save);
		*_ptr_li_t_save = save_ptr_temp;
		if (ft_strchr(*_ptr_li_t_save, '\n'))
			break ;
	}
	ft_free((void **)&buffer);
	return (_see_line_(_ptr_li_t_save, count, backup, line));
}

char	*get_next_line(int fd)
{
	char		*line_ptr;
	char		*buffer;
	static char	*_ptr_li_t_save;
	int			read_line;

	read_line = 0;
	if (fd < 0 || BUFFER_SIZE >= INT_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line_ptr = _read_fd_line(fd, buffer, &_ptr_li_t_save, read_line);
	return (line_ptr);
}
