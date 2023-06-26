/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:48:15 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/26 17:48:42 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

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
