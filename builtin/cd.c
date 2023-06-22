/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:20:51 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/22 18:16:50 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

int	cd_user(char **env, t_cmds *cmds)
{
	char	*dir;
	int		i;

	i = 0;
	dir = NULL;
	if (!ft_strncmp(cmds[0].cmds[i], "cd", 2) && cmds[0].cmds[i + 1]\
		&& !ft_strncmp(cmds[0].cmds[i + 1],"/Users", ft_strlen("/Users")))
	{
		dir = getcwd(NULL, 0);
		while (!ft_strncmp(dir, "/Users", ft_strlen("/Users")))
		{
			change_old(env);
			if (chdir("..") != 0)
			{
				perror(dir);
				return (0);
			}
			free(dir);
			dir = getcwd(NULL, 0);
			if (!ft_strncmp(dir, "/Users", ft_strlen("/Users") + 1))
			{
				if (chdir(dir) != 0)
				{
					perror(cmds[0].cmds[i + 1]);
					free(dir);
					return (0);
				}
				else
				{
					change_current_pwd(env);
					free(dir);
					return (1);
				}
			}
		}
	}	
	return (0);
}

int	cd_home(char **env, t_cmds *cmds)
{
	char	*dir;
	int		i;

	dir = NULL;
	i = 0;
	if (!ft_strncmp(cmds[0].cmds[i], "cd", 2) && !cmds[0].cmds[i + 1])
	{
		dir = go_home(env);
		if (chdir(dir) != 0)
		{
			perror(dir);
			free(dir);
			return (0);
		}
		else
		{
			free(dir);
			return (1);
		}
	}
	return (0);
}

int	change_dir(char **env, t_cmds *cmds)
{
	char	*dir;
	int		i;

	i = 0;
	if (cd_user(env, cmds))
		return (1);
	if (cd_home(env, cmds))
		return (1);
	if (!ft_strncmp(cmds[0].cmds[i], "cd", 2) && cmds[0].cmds[i + 1] && ft_strncmp(cmds[0].cmds[i + 1], "..", 3))
	{
		change_old(env);
		dir = get_path(cmds);
		if (chdir(dir) != 0)
		{
			perror(cmds[0].cmds[1]);
			free(dir);
			return (0);
		}
		change_current_pwd(env);
		free(dir);
	}
	if (!ft_strncmp(cmds[0].cmds[i], "cd", 2) && cmds[0].cmds[i + 1] && !ft_strncmp(cmds[0].cmds[i + 1], "..", 3))
	{
		change_old(env);
		if (chdir("..") != 0)
		{
			perror(cmds[0].cmds[1]);
			return (0);
		}
		change_current_pwd(env);
	}
	return (1);
}
