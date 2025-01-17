/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:35:28 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/16 18:29:25 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static char	*get_path_variable(char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	return (ft_strdup(env[i] + 5));
}

static char	*check_command_in_dir(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*find_executable_in_path(char *path, char *cmd)
{
	char	*dir;
	char	*full_path;

	dir = ft_strtok(path, ":");
	while (dir)
	{
		full_path = check_command_in_dir(dir, cmd);
		if (full_path)
			return (full_path);
		dir = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
	char	*path;
	char	*result;

	if (ft_strncmp(cmd, "./", 2) == 0)
		return (NULL);
	if (cmd[0] == '/' && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_path_variable(env);
	if (!path)
		return (NULL);
	result = find_executable_in_path(path, cmd);
	free(path);
	return (result);
}
