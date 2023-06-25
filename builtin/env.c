/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:55:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/25 15:01:18 by apaghera         ###   ########.fr       */
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
			printf("%s\n", env[i]);
			i++;
		}
	}
	return (1);
}
