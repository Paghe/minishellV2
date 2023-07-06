/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:49:08 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/04 17:36:21 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

int	ms_whitespace(char input)
{
	if (input && (input >= 0 && input <= 32))
		return (1);
	return (0);
}

void	remove_token(t_token *tokens)
{
	if (!tokens)
		return ;
	free(tokens->token);
	free(tokens);
	tokens = NULL;
}

int	begin_with_pipes(t_token *token)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd("`", 2);
	if (token->type == PIPE)
		ft_putstr_fd(token->token, 2);
	if (token->next && (is_symbol(token->next) || token->next->type == PIPE))
	{
		ft_putstr_fd(token->next->token, 2);
		if (token->next->next && token->next->next->type == PIPE)
			ft_putstr_fd(token->next->next->token, 2);
	}
	ft_putstr_fd("'", 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	not_correct_pos(t_token *current)
{
	if (current->next && (is_symbol(current->next) && !current->next->next))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (0);
	}
	return (1);
}
