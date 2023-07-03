/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:10:29 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/03 19:44:18 by apaghera         ###   ########.fr       */
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
			return (perror(pwd), 0);
		if (cmds[0].data.pipe_out != -1)
		{
			ft_putendl_fd(pwd, cmds[0].data.pipe_out);
			return (1);
		}
		else
		{
			ft_putendl_fd(pwd, 1);
			return (1);
		}
	}
	free(check_format);
	return (0);
}
