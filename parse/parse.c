/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:59:22 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 19:50:21 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

char	*escape_quote(char	*cmds)
{
	int		i;
	int		j;
	char	*new_cmds;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		if (cmds[i] != '\"' && cmds[i] != '\'')
			j++;
		i++;
	}
	new_cmds = malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (cmds[i])
	{
		if (cmds[i] && (cmds[i] != '\"' && cmds[i] != '\''))
			new_cmds[j++] = cmds[i];
		i++;
	}
	new_cmds[j] = '\0';
	return (new_cmds);
}

void	no_quote(t_cmds *cmds)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmds->cmds[i])
	{
		tmp = escape_quote(cmds->cmds[i]);
		if (cmds->cmds[i])
			free(cmds->cmds[i]);
		cmds->cmds[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}

t_token	*next_token(t_token *current)
{
	if (current)
	{
		current = current->next;
		return (current);
	}
	return (current);
}

void	add_cmds_env(t_cmds **cmds, char **envp, int i, int *j)
{
	cmds[i]->data.env = get_env_path(envp, cmds[i]->cmds[0]);
	(*j)++;
	cmds[i]->cmds[*j] = NULL;
}

void	parse_tokens(t_tokens *tokens, t_cmds **cmds, char **envp)
{
	t_token	*current;
	int		i;
	int		j;

	current = tokens->front;
	i = 0;
	j = 0;
	while (current)
	{
		current = handle_pipes(current, cmds, &i, &j);
		if (is_input_redirect(current))
			current = handle_input(current, cmds, i);
		else if (is_output_redirect(current))
			current = handle_output(current, cmds, i);
		else if (is_the_word(current) && \
					ft_strcmp(cmds[i]->data.input, current->token))
		{
			create_commands(cmds, current, i, j);
			add_cmds_env(cmds, envp, i, &j);
			current = next_token(current);
		}
		else
			current = next_token(current);
	}
}
