/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:27:24 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 16:03:36 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/lexer.h"

void	print_echo(t_cmds **cmds, int i)
{
	while (cmds[0]->cmds[i])
	{
		if (ft_strnstr(cmds[0]->cmds[i], "-n", ft_strlen(cmds[0]->cmds[i])))
			no_quote(*cmds);
		if (cmds[0]->data.pipe_out != -1)
			ft_putstr_fd(cmds[0]->cmds[i], cmds[0]->data.pipe_out);
		else
			ft_putstr_fd(cmds[0]->cmds[i], 1);
		if (cmds[0]->cmds[i + 1])
		{
			if (cmds[0]->data.pipe_out != -1)
				ft_putstr_fd(" ", cmds[0]->data.pipe_out);
			else
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
}

void	new_line_or_not(t_cmds **cmds, int no_newline)
{
	if (!no_newline)
	{
		if (cmds[0]->data.pipe_out != -1)
			ft_putstr_fd("\n", cmds[0]->data.pipe_out);
		else
			ft_putstr_fd("\n", 1);
	}
}

void	echo_with_arg(t_cmds **cmds, int no_newline, int i)
{
	if (!ft_strncmp(cmds[0]->cmds[i], "echo", 5))
	{
		if (cmds[0]->cmds[i + 1])
			i++;
		while (cmds[0]->cmds[i] && cmds[0]->cmds[i][0] != '\"' && \
				cmds[0]->cmds[i][0] != '\'' && \
					!ft_memcmp(cmds[0]->cmds[i], "-n", 2))
		{
			if (ft_strnstr(cmds[0]->cmds[i], "-n", ft_strlen(cmds[0]->cmds[i])))
				no_quote(*cmds);
			if (!ft_memcmp(cmds[0]->cmds[i], "-n", 2))
			{
				if (is_echo_newline(cmds[0]->cmds[i]))
					break ;
				else
					no_newline = 1;
			}
			i++;
		}
		print_echo(cmds, i);
		new_line_or_not(cmds, no_newline);
	}
}

void	echo_newline(t_cmds **cmds)
{
	int		no_newline;
	int		i;

	no_newline = 0;
	i = 0;
	while (cmds[0]->cmds[0][i])
	{
		cmds[0]->cmds[0][i] = ft_tolower(cmds[0]->cmds[0][i]);
		i++;
	}
	i = 0;
	if (only_echo(cmds))
		return ;
	echo_with_arg(cmds, no_newline, i);
}

int	echo(t_cmds *cmds)
{
	if (!ft_strncmp(cmds[0].cmds[0], "/bin/echo", 10))
	{
		free(cmds[0].cmds[0]);
		cmds[0].cmds[0] = ft_strdup("echo");
	}
	echo_newline(&cmds);
	return (1);
}
