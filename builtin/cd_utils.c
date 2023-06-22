/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:04:46 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/22 17:07:31 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

void	change_old(char **env)
{
	int		i;
	char	*old;

	i = 0;
	old = getcwd(NULL, 0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
		{
			env[i] = ft_strjoin("OLDPWD=", old);
			free(old);
			return ;
		}
		i++;
	}
	free(old);
}

char	*get_path(t_cmds *cmds)
{
	char	*tmp;
	char	*path;
	char	*dir;

	path = getcwd(NULL, 0);
	tmp = ft_strjoin(path, "/");
	if (cmds[0].cmds[1][0] == '/')
		dir = ft_strjoin(path, dir);
	else
		dir = ft_strjoin(tmp, cmds[0].cmds[1]);
	free(path);
	free(tmp);
	return (dir);
}

void	change_current_pwd(char **env)
{
	char	*current;
	int		i;

	i = 0;
	current = getcwd(NULL, 0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
		{
			env[i] = ft_strjoin("PWD=", current);
			free(current);
			return ;
		}
		i++;
	}
	free(current);
}

char	*go_home(char **env)
{
	int		i;
	char	*dir;

	i = 0;
	dir = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
		{
			dir = ft_strdup(env[i] + 5);
			return (dir);
		}
		i++;
	}
	return (dir);
}
