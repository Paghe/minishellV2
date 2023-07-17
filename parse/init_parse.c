/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:34:12 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/17 14:12:26 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

t_cmds	**data_exec(t_cmds **cmds, int i)
{
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
	return (cmds);
}

t_token	*set_space_arg(t_token *current, int *len)
{
	while (current && current->type != PIPE)
	{
		(*len)++;
		current = current->next;
	}
	return (current);
}

t_token	*next_token_parse(t_token *current)
{
	if (current)
	current = current->next;
	return (current);
}

t_cmds	**allocate_memory(t_cmds **cmds, t_tokens *tokens, \
								int *total_commands)
{
	*total_commands = count_commands(tokens);
	cmds = malloc(sizeof(t_cmds *) * (*total_commands + 1));
	return (cmds);
}

t_cmds	**init_list_commands(t_tokens *tokens, t_cmds **cmds)
{
	int		i;
	int		len;
	t_token	*current;
	int		j;
	int		total_commands;

	i = -1;
	j = 0;
	cmds = allocate_memory(cmds, tokens, &total_commands);
	current = tokens->front;
	while (++i <= total_commands)
	{
		cmds[i] = malloc(sizeof(t_cmds));
		len = 0;
		current = set_space_arg(current, &len);
		cmds[i]->cmds = malloc(sizeof(char *) * (len + 1));
		j = 0;
		while (cmds[i]->cmds[j] && j < len)
			cmds[i]->cmds[j++] = NULL;
		cmds = data_exec(cmds, i);
		current = next_token_parse(current);
	}
	cmds[total_commands] = NULL;
	return (cmds);
}
