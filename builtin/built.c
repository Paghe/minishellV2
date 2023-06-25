/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:15:04 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/25 16:34:03 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

int	if_is_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	i = 0;
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_memcmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}

int	built_in(t_cmds *cmds, char **env)
{
	int	flag;

	flag = 0;
	if (echo(cmds))
		flag = 1;
	if (change_dir(env, cmds))
		flag = 1;
	if (get_env(cmds, env))
		flag = 1;
	if (build_pwd(cmds))
		flag = 1;
	return (flag);
}
