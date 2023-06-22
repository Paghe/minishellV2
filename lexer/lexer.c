/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:48:23 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/21 20:18:30 by apaghera         ###   ########.fr       */
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

/* char	*replace_spaces(char *str)
{
	size_t	i;
	size_t	j;
	char	buffer[LINEBUFFER_MAX];
	int		squote;
	int		dquote;

	i = 0;
	j = 0;
	squote = 0;
	dquote = 0;
	while (ms_whitespace(str[i]))
		i++;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\"' && !squote)
			dquote ^= 1;
		if (str[i] == '\'' && !dquote)
			squote ^= 1;
		if (str[i] == ' ' && (!squote && !dquote))
		{
			printf("%c", buffer[j]);
			while (ms_whitespace(str[i]) && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				break ;
			else
				buffer[j++] = ' ';
		}
		buffer[j] = str[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	free(str);
	return (ft_strdup(buffer));
} */

char	*replace_spaces(char *str)
{
	size_t	i;
	size_t	j;
	char	buffer[LINEBUFFER_MAX];
	int		squote;
	int		dquote;

	i = 0;
	j = 0;
	squote = 0;
	dquote = 0;
	while (ms_whitespace(str[i]))
		i++;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\"' && !squote)
			dquote ^= 1;
		if (str[i] == '\'' && !dquote)
			squote ^= 1;
		if ((str[i] == ' ' || str[i] == '\t') && (!squote && !dquote))
		{
			if (j > 0 && buffer[j - 1] != ' ' && buffer[j - 1] != '\t')
				buffer[j++] = ' ';
		}
		else
			buffer[j++] = str[i];
		i++;
	}
	buffer[j] = '\0';
	free(str);
	return (ft_strdup(buffer));
}

char	*format_line(char *line)
{
	char	buffer[LINEBUFFER_MAX];
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '>')|| (line[i] == '<' && line[i + 1] == '<'))
		{
			buffer[count] = ' ';
			buffer[count + 1] = format_is_symbol(line[i]);
			buffer[count + 2] = format_is_symbol(line[i]);
			buffer[count + 3] = ' ';
			i++;
			count += 4;
		}
		else if (line[i] == format_is_symbol(line[i]))
		{
			buffer[count] = ' ';
			buffer[count + 1] = format_is_symbol(line[i]);
			buffer[count + 2] = ' ';
			count += 3;
		}
		else
		{
			buffer[count] = line[i];
			count++;
		}
		i++;
	}
	buffer[count] = '\0';
	return (ft_strdup(buffer));
}

void	parsing(t_lexer *lexer, char *input)
{
	int		i;
	char	buffer[LINEBUFFER_MAX];
	size_t	len;
	char	current;
	char	next;
	char	*line;
	char	*buf_ptr;
	int		squote;
	int		dquote;
	char	*good_line;

	i = 0;
	line = replace_spaces(input);
	good_line = format_line(line);
	good_line = replace_spaces(good_line);
	good_line = ft_strtrim(good_line, " ");
	len = min(ft_strlen(good_line), LINEBUFFER_MAX);
	ft_memcpy(buffer, good_line, len);
	buffer[len] = '\0';
	lexer->tokens = create_tokens();
	squote = 0;
	dquote = 0;
	buf_ptr = buffer;
	while (i < (int)len)
	{
		current = good_line[i];
		if (current == '\"' && !squote)
			dquote ^= 1;
		if (current == '\'' && !dquote)
			squote ^= 1;
		if (i <= (int)len)
			next = good_line[i + 1];
		else
			i = 0;
		if (((current == ' ' && good_line[i + 1] != ' ' && next) || current == '\0') && !squote && !dquote)
		{
			buffer[i] = '\0';
			add_token(lexer->tokens, buf_ptr, buf_ptr);
			buf_ptr += ft_strlen(buf_ptr) + 1;
		}
		i++;
	}
	add_token(lexer->tokens, buf_ptr, buf_ptr);
/* 	print_token(lexer->tokens); */
	free(good_line);
	free(line);
}
