/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:39:03 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/10 11:43:58 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

char *find_command_path(char *cmd, char **env)
{
    char *path;
    char *dir;
    char *full_path;
    int i;

    // Check if the command already contains a path (e.g., "/bin/ls")
    if (access(cmd, X_OK) == 0)
        return (cmd);

    // Search for the PATH variable in the environment
    i = 0;
    while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
        i++;

    if (!env[i])
        return (NULL); // PATH variable not found

    // Extract the PATH value
    path = ft_strdup(env[i] + 5); // Skip "PATH="
    if (!path)
        return (NULL);

    // Split the PATH into directories
    dir = strtok(path, ":");
    while (dir)
    {
        // Construct the full path (e.g., "/bin/ls")
        full_path = ft_strjoin(dir, "/");
        full_path = ft_strjoin(full_path, cmd);

        // Check if the command exists and is executable
        if (access(full_path, X_OK) == 0)
        {
            free(path);
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path);
    return (NULL); // Command not found in PATH
}