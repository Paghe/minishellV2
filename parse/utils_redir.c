/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:47:20 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 21:22:44 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	redirect_io(int input, int output)
{
	if (input != -1)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}	
	if (output != -1)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
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
