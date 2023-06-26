/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:59:22 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/22 14:16:32 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

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
		{
			new_cmds[j] = cmds[i];
			j++;
		}
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

int	count_commands(t_tokens	*tokens)
{
	t_token	*current;
	int		count;

	count = 1;
	current = tokens->front;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void	parse_tokens(t_tokens *tokens, t_cmds **cmds, char **envp)
{
	t_token	*current;
	int		i;
	int		j;
	int		fd;

	current = tokens->front;
	i = 0;
	j = 0;
	while (current)
	{
		if (current->type == PIPE)
		{
			init_pipes(cmds, i);
			i++;
			current = current->next;
			j = 0;
		}
		if (is_input_redirect(current))
		{
			if (current->next && is_the_word(current->next))
			{
				if (cmds[i]->data.input)
					free(cmds[i]->data.input);
				cmds[i]->data.input = ft_strdup(current->next->token);
				current = current->next;
			}
		}
		else if (is_output_redirect(current))
		{
			if (current->type == DMORE)
				cmds[i]->data.is_append = 1;
			if (current->next && is_the_word(current->next))
			{
				if (cmds[i]->data.output)
					free(cmds[i]->data.output);
				cmds[i]->data.output = ft_strdup(current->next->token);
				fd = open(current->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				close(fd);
				current = current->next;
			}
		}
		else
		{
			if (cmds[i]->data.env)
				free(cmds[i]->data.env);
			cmds[i]->cmds[j] = ft_strdup(current->token);
			/* if (current->type == DQUOTE)
				cmds[i]->data.type = DOQUOTE;
			if (current->type == SQUOTE)
				cmds[i]->data.type = SIQUOTE; */
			cmds[i]->data.env = get_env_path(envp, cmds[i]->cmds[0]);
			j++;
			cmds[i]->cmds[j] = NULL;
		}
		if (current)
			current = current->next;
	}
}

void	replace_env_vars(t_cmds **cmds, char **envp)
{
	int		i;
	int		j;
	char	*arg;
	char	*value;
	int		dollars;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i]->cmds[j])
		{
			arg = cmds[i]->cmds[j];
			dollars = count_dollars(arg);
			if ((arg = ft_strrchr(arg, '$')) && dollars % 2 != 0)
			{
				if (*(arg + 1) == '?')
					value = ft_itoa(EXIT_C);
				else
					value = get_env_var(arg + 1, envp);
				if (!value)
					cmds[i]->cmds[j] = ft_strdup("");
				else
				{
					arg = ft_strdup2(cmds[i]->cmds[j], dollars - 1);
					value = ft_strjoin(arg, value);
					free(arg);
					free(cmds[i]->cmds[j]);
					cmds[i]->cmds[j] = ft_strdup(value);
					free(value);
				}
			}
			j++;
		}
		i++;
	}
}

void	free_parse(t_cmds **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i]->cmds[j])
		{
			free(cmds[i]->cmds[j]);
			j++;
		}
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
