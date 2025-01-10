/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:39:03 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/10 17:28:32 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

char *find_command_path(char *cmd, char **env)
{
    char *path;
    char *dir;
    char *full_path;
	char	*temp;
    int i;

    if (access(cmd, X_OK) == 0)
        return (ft_strdup(cmd));
	

    i = 0;
    while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
        i++;

    if (!env[i])
        return (NULL);

    path = ft_strdup(env[i] + 5);
    if (!path)
        return (NULL);

    dir = ft_strtok(path, ":");
    while (dir)
    {
        temp = ft_strjoin(dir, "/");
		if (!temp)
			(error_and_exit("ft_strjoin temp failed\n", 1), free(path));
        full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			(error_and_exit("ft_strjoin full_path failed\n", 1), free(path));

        if (access(full_path, X_OK) == 0)
        {
            free(path);
            return (full_path);
        }

        free(full_path);
        dir = ft_strtok(NULL, ":");
    }

    free(path);
    return (NULL);
}
