/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:48:23 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/15 17:48:15 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	print_token(t_tokens *tokens)
{
	t_token	*current;

	current = tokens->front;
	while (current)
	{
		printf("[%s]\t [", current->token);
		print_token_type(current->type);
		printf("]\n");
		current = current->next;
	}
}

int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

char	next_value_char(int i, char *good_line, char next)
{
	if (i <= min(ft_strlen(good_line), LINEBUFFER_MAX))
		next = good_line[i + 1];
	if (next)
		return (next);
	else
		return (0);
}

void	token_parse(t_lexer *lexer, char *buffer, \
						char *good_line, char *buf_ptr)
{
	int		i;
	int		dquote;
	int		squote;
	char	current;
	char	next;

	i = -1;
	dquote = 0;
	squote = 0;
	while (++i < min(ft_strlen(good_line), LINEBUFFER_MAX))
	{
		current = good_line[i];
		dquote = have_dquote(current, squote, dquote);
		squote = have_squote(current, squote, dquote);
		next = next_value_char(i, good_line, next);
		if (((current == ' ' && good_line[i + 1] != ' ' && next) || \
				current == '\0') && !squote && !dquote)
		{
			buffer[i] = '\0';
			add_token(lexer->tokens, buf_ptr, buf_ptr);
			buf_ptr += ft_strlen(buf_ptr) + 1;
		}
	}
	add_token(lexer->tokens, buf_ptr, buf_ptr);
}

void	parsing(t_lexer *lexer, char *input)
{
	char	buffer[LINEBUFFER_MAX];
	char	*line;
	char	*buf_ptr;
	char	*good_line;
	char	*tmp;

	line = replace_spaces(input);
	good_line = format_line(line);
	free(line);
	tmp = replace_spaces(good_line);
	good_line = ft_strtrim(tmp, " ");
	free(tmp);
	lexer->tokens = create_tokens();
	buf_ptr = buffer;
	tokenize_input_init(lexer, buffer, \
						good_line, buf_ptr);
}
