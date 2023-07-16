/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:15:04 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 19:36:43 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

char	*modify_command(char *cmd)
{
	int		i;
	char	*check_format;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	check_format = escape_quote(cmd);
	if (!ft_strncmp(check_format, "/bin/echo", 10))
	{
		free(check_format);
		check_format = ft_strdup("echo");
	}
	return (check_format);
}

int	if_is_builtin(char *cmd)
{
	char	*check_format;

	check_format = modify_command(cmd);
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

int	exit_format(int i, t_cmds *cmds, int flag, int *exit)
{
	if (i > 1 && !is_number(cmds->cmds[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmds->cmds[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		EXIT_C = 255;
	}
	else if (i > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		EXIT_C = 1;
	}
	else if (i == 2)
	{
		EXIT_C = ft_atoi(cmds->cmds[1]);
		*exit = 15;
	}
	else
		*exit = 15;
	return (flag = 1);
}

int	built_in(t_cmds *cmds, char ***env, char ***shell_envp, int *exit)
{
	int		flag;

	flag = 0;
	flag = if_is_exit(cmds, flag, exit);
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
	if (change_dir(*shell_envp, cmds))
		flag = 1;
	if (get_env(cmds, *shell_envp))
		flag = 1;
	if (build_pwd(cmds))
		flag = 1;
	return (flag);
}
