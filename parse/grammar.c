/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:34:03 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/04 17:37:16 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	check_first_token(t_token	*token)
{
	t_token	*current;

	current = token;
	if (is_word(current) || is_symbol(current))
		return (1);
	if (begin_with_pipes(current))
		return (0);
	return (0);
}

int	is_pipe(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->type == PIPE)
	{
		if (current->next->type == WORD || is_symbol(current))
			return (1);
	}
	if (is_word(current) || is_symbol(current))
		return (1);
	return (0);
}

int	get_symbol(t_token *token)
{
	t_token	*current;

	current = token;
	if (is_symbol(current))
	{
		if (current->next->type == WORD)
			return (1);
	}
	if (is_word(current) || current->type == PIPE)
		return (1);
	return (0);
}

int	check_last_token(t_tokens *tokens, t_token *current)
{
	if (is_word(current))
		return (1);
	else
	{
		if (tokens->size == 1)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (0);
		}
		else
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (0);
		}
		return (0);
	}
}

int	get_grammar(t_tokens *tokens)
{
	t_token	*current;

	current = tokens->front;
	if (!not_correct_pos(current))
		return (0);
	if (!check_first_token(current))
		return (0);
	while (current && current->next)
	{
		if (!get_symbol(current))
		{
			if (begin_with_pipes(current))
				return (0);
		}
		if (!is_pipe(current))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (0);
		}
		current = current->next;
	}
	if (!check_last_token(tokens, current))
		return (0);
	return (1);
}
