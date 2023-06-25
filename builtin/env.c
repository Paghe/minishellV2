/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:55:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/25 15:14:53 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

int	get_env(t_cmds *cmds, char **env)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cmds[0].cmds[0], "env", 4))
	{
		while (env[i])
		{
			if (cmds[0].data.pipe_out != -1)
			{
				ft_putstr_fd(env[i], cmds[0].data.pipe_out);
				ft_putstr_fd("\n", cmds[0].data.pipe_out);
			}
			else
			{
				ft_putstr_fd(env[i], 1);
				ft_putstr_fd("\n", 1);
			}
			i++;
		}
	}
	return (1);
}
