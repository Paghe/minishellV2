/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:19:33 by crepou            #+#    #+#             */
/*   Updated: 2023/07/16 18:46:52 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*get_env_path(char **envp, char *command)
{
	char	*path;
	char	*cmd_path;
	int		i;
	char	**paths;
	char	*cmd;
	char	*tmp_path;

	i = -1;
	path = NULL;
	tmp_path = NULL;
	while (envp[++i])
	{
		if (envp[i] == ft_strnstr(envp[i], "PATH", 4))
		{
			if (tmp_path)
				free(tmp_path);
			path = ft_strdup(envp[i]);
			tmp_path = path;
		}
	}
	if (!path)
		return (NULL);
	paths = ft_split(path + 5, ':');
	if (ft_strrchr(command, '/') == ft_strchr(command, '/') && *command == '/' && !if_is_builtin(command))
	{
		free(path);
		free_paths(paths);
		return 	NULL;
	}
	if (command && ft_strrchr(command, '/') && (ft_strrchr(command, '/') != ft_strchr(command, '/')))
		cmd = strrchr(command, '/') + 1;
	else
		cmd = command;
	free(path);
	i = -1;
	while (paths[++i])
	{
		cmd_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		ft_strcpy(cmd_path, paths[i]); // Implement strcpy
		ft_strcat(cmd_path, "/");	// Implement strcat
		ft_strcat(cmd_path, cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free_paths(paths); // free stuff looks above
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_paths(paths);
	if (if_is_builtin(cmd))
		return (ft_strdup(cmd));
	return (NULL); // this way is way faster to allocate memory 
}
