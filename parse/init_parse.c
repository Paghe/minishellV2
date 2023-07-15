/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:34:12 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/15 19:12:11 by crepou           ###   ########.fr       */
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
	int j = 0;
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
		j = 0;
		while (cmds[i]->cmds[j] && j < len)
		{
			cmds[i]->cmds[j] = NULL;
			j++;	
		}
		cmds[i]->data.input = NULL;
		cmds[i]->data.output = NULL;
		cmds[i]->data.env = NULL;
		cmds[i]->data.pipe_in = -1;
		cmds[i]->data.pipe_out = -1;
		cmds[i]->data.fd_in = -1;
		cmds[i]->data.fd_out = -1;
		cmds[i]->data.is_append = 0;
		cmds[i]->data.is_redir_first = 0;
		cmds[i]->data.is_updated = 0;
		cmds[i]->data.out_redir_first = 0;
		cmds[i]->data.exist = 0;
		if (current)
			current = current->next;
		i++;
	}
	cmds[total_commands] = NULL;
	return (cmds);
}
