/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:34:12 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/22 14:36:39 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

t_cmds	**init_list_commands(t_tokens *tokens)
{
	int		i;
	int		total_commands;
	int		len;
	t_token	*current;
	t_cmds	**cmds;

	i = 0;
	total_commands = count_commands(tokens);
	cmds = malloc(sizeof(t_cmds *) * (total_commands + 1));
	current = tokens->front;
	while (i < total_commands)
	{
		cmds[i] = malloc(sizeof(t_cmds));
		len = 0;
		while (current && current->type != PIPE)
		{
			len++;
			current = current->next;
		}
		cmds[i]->cmds = malloc(sizeof(char *) * (len + 1));
		if (cmds[i]->cmds)
			cmds[i]->cmds[len] = NULL;
		cmds[i]->data.input = NULL;
		cmds[i]->data.output = NULL;
		cmds[i]->data.env = NULL;
		cmds[i]->data.pipe_in = -1;
		cmds[i]->data.pipe_out = -1;
		cmds[i]->data.fd_in = -1;
		cmds[i]->data.fd_out = -1;
		cmds[i]->data.is_append = 0;
		if (current)
			current = current->next;
		i++;
	}
	cmds[total_commands] = NULL;
	return (cmds);
}
