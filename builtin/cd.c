/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:20:51 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/22 15:09:22 by apaghera         ###   ########.fr       */
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

int	change_dir(char **env, t_cmds *cmds)
{
	char	*dir;
	int		i;

	i = 0;
	if (!ft_strncmp(cmds[0].cmds[i], "cd", 2) && !ft_strncmp(cmds[0].cmds[i + 1],"/Users", ft_strlen("/Users")))
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
					return (0);
				}
				else
				{
					change_current_pwd(env);
					return (1);
				}
			}
		}
	}	
	if (!ft_strncmp(cmds[0].cmds[i], "cd", 2) && !cmds[0].cmds[i + 1])
	{
		dir = go_home(env);
		if (chdir(dir) != 0)
		{
			perror(dir);
			free(dir);
			return (0);
		}
	}
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
