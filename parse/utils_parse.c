/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:40:36 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/04 17:24:34 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	is_symbol(t_token *token)
{
	if (token->type == DMORE || token->type == DLESS || \
				token->type == LESS || token->type == MORE)
		return (1);
	return (0);
}

int	is_word(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->type == DQUOTE || current->type == SQUOTE || \
			current->type == WORD)
		return (1);
	return (0);
}

int	is_input_redirect(t_token *token)
{
	return (token->type == LESS || token->type == DLESS);
}

int	is_output_redirect(t_token *token)
{
	return (token->type == MORE || token->type == DMORE);
}

int	is_the_word(t_token *token)
{
	return (token->type == WORD || token->type == SQUOTE || \
		token->type == DQUOTE);
}
