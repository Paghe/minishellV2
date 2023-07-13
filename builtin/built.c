/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:15:04 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/13 12:52:02 by crepou           ###   ########.fr       */
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
	if (!ft_memcmp(check_format, "unset", 6))
		return (free(check_format), 1);
	if (!ft_memcmp(check_format, "exit", 5))
		return (free(check_format), 1);
	return (free(check_format), 0);
}

int	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	built_in(t_cmds *cmds, char ***env, char ***shell_envp, int *exit)
{
	int	flag;
	int	i;
	char *tmp;
	char	*exit_msg;

	flag = 0;
	if (ft_memcmp(cmds->cmds[0], "exit", 5) == 0)
	{
			i = 0;
			while(cmds->cmds[i])
				i++;
			if (i > 1 && !is_number(cmds->cmds[1]))
			{
				tmp = ft_strjoin("minishell: exit: ",cmds->cmds[1]);
				exit_msg = ft_strjoin(tmp, ": numeric argument required");
				ft_putendl_fd(exit_msg, 2);
				free(tmp);
				free(exit_msg);
				EXIT_C = 0;
			}
			else if (i > 2)
			{
				ft_putendl_fd("minishell: exit: too many arguments", 2);
				EXIT_C = 0;
			}
			*exit = 15;
			flag = 1;
	}
	if (ft_memcmp(cmds->cmds[0], "export", 7) == 0)
	{
		export(cmds->cmds, env, shell_envp);
		flag = 1;
	}
	if (ft_memcmp(cmds->cmds[0], "unset", 6) == 0)
	{
		unset(env, cmds->cmds[1]);
		unset(shell_envp, cmds->cmds[1]);
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
