/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:32:59 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/14 16:38:16 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	here_doc(t_token *token, t_cmds *cmds)
{
	t_token	*current;
	char	*delimiter;
	char	*line;

	delimiter = NULL;
	line = NULL;
	current = token;
	delimiter = ft_strdup(current->token);
	cmds->data.fd_in = open("temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, cmds->data.fd_in);
		free (line);
	}
	free(delimiter);
}
