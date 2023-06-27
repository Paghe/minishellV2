/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:48:15 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/27 15:34:43 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

int	go_to_user(t_cmds *cmds, char *dir, char **env)
{
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
				perror(cmds[0].cmds[1]);
				return (free(dir), 0);
			}
			else
			{
				change_current_pwd(env);
				return (free(dir), 1);
			}
		}
	}
	return (0);
}

int	is_void_pwd(t_cmds *cmds)
{
	int		i;
	int		is_void;

	i = 1;
	is_void = 0;
	if (cmds[0].cmds[i] && !ft_strncmp(cmds[0].cmds[i], "/", ft_strlen("/")))
	{
		i++;
		if (!(cmds[0].cmds[i]))
			is_void = 1;
		else if (!ft_strncmp(cmds[0].cmds[i], "/", ft_strlen("/")))
			is_void = 1;
	}
	return (is_void);
}
