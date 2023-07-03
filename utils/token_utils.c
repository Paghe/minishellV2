/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:46:00 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/03 19:47:12 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parse.h"

void	destroy_node(t_token *token)
{
	if (!token)
		return ;
	free(token->token);
	destroy_node(token->next);
	free(token);
}

void	destroy_tokens(t_tokens *tokens)
{
	if (!tokens)
		return ;
	destroy_node(tokens->front);
	free(tokens);
}
