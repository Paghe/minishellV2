/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:10:29 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/26 15:10:41 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	build_pwd(t_cmds *cmds)
{
	char	*pwd;
	char	*check_format;	

	check_format = escape_quote(cmds[0].cmds[0]);
	if (!ft_strncmp(check_format, "pwd", 4))
	{
		free(check_format);
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			ft_putstr_fd("error", 2);
			return (0);
		}
		if (cmds[0].data.pipe_out != -1)
		{
			ft_putstr_fd(pwd, cmds[0].data.pipe_out);
			ft_putstr_fd("\n", cmds[0].data.pipe_out);
			return (1);
		}
		else
		{
			ft_putstr_fd(pwd, 1);
			ft_putstr_fd("\n", 1);
			return (1);
		}
	}
	free(check_format);
	return (0);
}
