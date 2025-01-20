/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:07:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/19 17:46:15 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static	void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strchr(const char *str, int search)
{
	return (ft_memchr(str, search, ft_strlen(str) + 1));
}

static char	*skip_delimiters(char *str, const char *delim)
{
	while (*str && ft_strchr(delim, *str))
		str++;
	return (str);
}

static char	*find_token_end(char *str, const char *delim)
{
	while (*str && !ft_strchr(delim, *str))
		str++;
	return (str);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next;
	char		*start;
	char		*end;

	if (str != NULL)
		next = str;
	if (next == NULL)
		return (NULL);
	start = skip_delimiters(next, delim);
	if (*start == '\0')
	{
		next = NULL;
		return (NULL);
	}
	end = find_token_end(start, delim);
	if (*end != '\0')
	{
		*end = '\0';
		next = end + 1;
	}
	else
		next = NULL;
	return (start);
}
