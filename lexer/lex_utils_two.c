/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:18:33 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/03 19:50:01 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	tokenize_input_init(t_lexer *lexer, char *buffer, \
						char *good_line, char *buf_ptr)
{
	size_t	len;

	len = min(ft_strlen(good_line), LINEBUFFER_MAX);
	ft_memcpy(buffer, good_line, len);
	buffer[len] = '\0';
	token_parse(lexer, buffer, \
					good_line, buf_ptr);
	free(good_line);
}

char	*replace_spaces(char *str)
{
	size_t	i;
	size_t	j;
	char	buffer[LINEBUFFER_MAX];
	int		squote;
	int		dquote;

	i = skip_whitespaces(str);
	j = 0;
	squote = 0;
	dquote = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\"' && !squote)
			dquote ^= 1;
		if (str[i] == '\'' && !dquote)
			squote ^= 1;
		if ((str[i] == ' ' || str[i] == '\t') && (!squote && !dquote))
			j = give_a_space(buffer, j);
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
		if ((line[i] == '>' && line[i + 1] == '>') || \
			(line[i] == '<' && line[i + 1] == '<'))
				count = space_double_symbol(line, buffer, count, &i);
		else if (line[i] == format_is_symbol(line[i]))
			count = space_single_symbol(line, buffer, count, &i);
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

int	have_dquote(char current, int squote, int dquote)
{
	if (current == '\"' && !squote)
			dquote ^= 1;
	return (dquote);
}

int	have_squote(char current, int squote, int dquote)
{
	if (current == '\'' && !dquote)
			squote ^= 1;
	return (squote);
}
