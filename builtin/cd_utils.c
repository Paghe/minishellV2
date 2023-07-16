/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:04:46 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 18:29:50 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

void	change_old(char **env)
{
	int		i;
	char	*old;
	char	*tmp;

	i = 0;
	old = getcwd(NULL, 0);
	if (!old)
		perror(old);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
		{
			tmp = ft_strjoin("OLDPWD=", old);
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", old);
			free(old);
			free(tmp);
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

	dir = NULL;
	path = getcwd(NULL, 0);
	if (!path)
		perror(path);
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
	char	*tmp;

	i = 0;
	current = getcwd(NULL, 0);
	if (!current)
		perror(current);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
		{
			tmp = ft_strjoin("PWD=", current);
			free(env[i]);
			env[i] = ft_strjoin("PWD=", current);
			free(current);
			free(tmp);
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

int	pwd_goes_void(char **env, t_cmds *cmds)
{
	char	*dir;
	int		is_void;

	dir = NULL;
	is_void = 0;
	dir = getcwd(NULL, 0);
	if (!dir)
		perror(dir);
	is_void = is_void_pwd(cmds);
	if (!dir || !is_void)
		return (0);
	free(dir);
	dir = ft_strdup(cmds[0].cmds[1]);
	if (chdir(dir) != 0)
		return (perror(dir), 0);
	else
	{
		change_old(env);
		change_current_pwd(env);
		free(dir);
		return (1);
	}
	free(dir);
	return (0);
}
