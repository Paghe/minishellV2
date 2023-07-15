/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:47:20 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/14 18:15:11 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	redirect_io(int input, int output)
{
	if (input)
	{
		dup2(input, STDIN_FILENO);
	}	
	if (output)
		dup2(output, STDOUT_FILENO);
}

char	**escape_quotes_cmds(char **cmds)
{
	int		i;
	char	*trimed;

	i = 0;
	trimed = NULL;
	while (cmds[i])
	{
		if (ft_strncmp(cmds[i], "\"", 1) == 0)
		{
			trimed = ft_strtrim(cmds[i], "\"");
			free(cmds[i]);
			cmds[i] = ft_strdup(trimed);
			free(trimed);
		}
		if (ft_strncmp(cmds[i], "\'", 1) == 0)
		{
			trimed = ft_strtrim(cmds[i], "\'");
			free(cmds[i]);
			cmds[i] = ft_strdup(trimed);
			free(trimed);
		}
		i++;
	}
	return (cmds);
}
