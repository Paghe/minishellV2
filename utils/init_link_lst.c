/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_link_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:00:08 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/03 19:47:34 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

t_tokens	*create_tokens(void)
{
	t_tokens	*tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->front = NULL;
	tokens->rear = NULL;
	tokens->size = 0;
	return (tokens);
}

t_token_type	get_token_type(char *format)
{
	if (format[0] == '\"')
		return (DQUOTE);
	if (format[0] == '\'')
		return (SQUOTE);
	else if (!ft_strncmp(format, ">>", 3))
		return (DMORE);
	else if (!ft_strncmp(format, "<<", 3))
		return (DLESS);
	else if (!ft_strncmp(format, ">", 2))
		return (MORE);
	else if (!ft_strncmp(format, "<", 2))
		return (LESS);
	else if (!ft_strncmp(format, "|", 2))
		return (PIPE);
	return (WORD);
}

void	print_token_type(t_token_type type)
{
	if (type == WORD)
		printf("WORD");
	else if (type == DQUOTE)
		printf("DQUOTE");
	else if (type == SQUOTE)
		printf("SQUOTE");
	else if (type == MORE)
		printf("MORE");
	else if (type == LESS)
		printf("LESS");
	else if (type == DMORE)
		printf("DMORE");
	else if (type == DLESS)
		printf("DLESS");
	else if (type == PIPE)
		printf("PIPE");
	else if (type == DOLLAR)
		printf("DOLLAR");
}

t_token	*new_token(char *format)
{
	t_token	*new_token;
	char	*new_format;

	new_format = ft_strdup(format);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = new_format;
	new_token->type = get_token_type(format);
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_tokens *tokens, char *format, char *type)
{
	t_token	*token;

	if (!format || !type)
		return ;
	token = new_token(format);
	if (!token)
		return ;
	if (tokens->size == 0)
	{
		tokens->front = token;
		tokens->rear = token;
	}
	else
	{
		tokens->rear->next = token;
		tokens->rear = tokens->rear->next;
	}
	tokens->size++;
}
