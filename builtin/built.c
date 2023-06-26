/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:15:04 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/25 17:51:56 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

int	if_is_builtin(char *cmd)
{
	int		i;
	char	*check_format;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	i = 0;
	check_format = escape_quote(cmd);
	if (!ft_strncmp(check_format, "echo", 5))
		return (free(check_format), 1);
	if (!ft_memcmp(check_format, "cd", 3))
		return (free(check_format), 1);
	if (!ft_strncmp(check_format, "env", 4))
		return (free(check_format), 1);
	if (!ft_strncmp(check_format, "pwd", 4))
		return (free(check_format), 1);
	if (!ft_strncmp(check_format, "unset", 6))
		return (free(check_format), 1);
	if (!ft_memcmp(check_format, "export", 7))
		return (free(check_format), 1);
	return (free(check_format), 0);
}

int	built_in(t_cmds *cmds, char ***env, char ***shell_envp)
{
	int	flag;

	flag = 0;
	if (ft_memcmp(cmds->cmds[0], "export", 6) == 0)
	{
		export(cmds->cmds, env, shell_envp);
		flag = 1;
	}
	if (echo(cmds))
		flag = 1;
	if (change_dir(*env, cmds))
		flag = 1;
	if (get_env(cmds, *env))
		flag = 1;
	if (build_pwd(cmds))
		flag = 1;
	return (flag);
}