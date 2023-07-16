/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:01:16 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 16:01:51 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

void	free_parse(t_cmds **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i]->cmds && cmds[i]->cmds[j])
		{
			if (cmds[i]->data.exist)
				free(cmds[i]->cmds[j]);
			j++;
		}
		if (cmds[i]->cmds)
			free(cmds[i]->cmds);
		if (cmds[i]->data.input)
			free(cmds[i]->data.input);
		if (cmds[i]->data.output)
			free(cmds[i]->data.output);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

t_token	*handle_input(t_token *current, t_cmds **cmds, int i)
{
	if (current->type == DLESS)
	{
		current = current->next;
		if (cmds[i]->data.input)
			free(cmds[i]->data.input);
		cmds[i]->data.input = ft_strdup("temp_file");
		here_doc(current, cmds[i]);
		if (current->next && is_the_word(current))
			current = current->next;
		else
			return (NULL);
	}
	if ((current->type == LESS) && \
		(current->next && is_the_word(current->next)))
	{
		current = current->next;
		if (cmds[i]->data.input)
			free(cmds[i]->data.input);
		cmds[i]->data.input = ft_strdup(current->token);
		if (current->next)
			current = current->next;
	}
	return (current);
}

t_token	*handle_output(t_token *current, t_cmds **cmds, int i)
{
	int	fd;

	fd = 0;
	if (current->type == DMORE)
		cmds[i]->data.is_append = 1;
	if (current->next && is_the_word(current->next))
	{
		if (cmds[i]->data.output)
			free(cmds[i]->data.output);
		cmds[i]->data.output = ft_strdup(current->next->token);
		if (cmds[i]->data.is_append)
			fd = open(current->next->token, O_WRONLY | O_CREAT | \
						O_APPEND, 0644);
		else
			fd = open(current->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(fd);
		current = current->next;
		if (current->next && is_the_word(current->next))
			cmds[i]->data.exist = 1;
	}
	return (current);
}

void	create_commands(t_cmds **cmds, t_token *current, int i, int j)
{
	char	*tmp;

	tmp = NULL;
	if (cmds[i]->data.env)
		free(cmds[i]->data.env);
	cmds[i]->cmds[j] = ft_strdup(current->token);
	cmds[i]->data.exist = 1;
	tmp = ft_strtrim(cmds[i]->cmds[0], "\"");
	if (cmds[i]->cmds[0])
		free(cmds[i]->cmds[0]);
	cmds[i]->cmds[0] = ft_strdup(tmp);
	free(tmp);
}

t_token	*handle_pipes(t_token *current, t_cmds **cmds, int *i, int *j)
{
	if (current->type == PIPE)
	{
		init_pipes(cmds, *i);
		(*i)++;
		*j = 0;
	}
	return (current);
}
