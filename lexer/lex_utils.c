/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:20:03 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/28 13:51:26 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

char	format_is_symbol(char symbol)
{
	if (symbol == '<' || symbol == '>' || symbol == '|')
		return (symbol);
	return (0);
}

int	skip_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (ms_whitespace(str[i]))
		i++;
	return (i);
}

int	give_a_space(char *buffer, int j)
{
	if (j > 0 && buffer[j - 1] != ' ' && buffer[j - 1] != '\t')
		buffer[j++] = ' ';
	return (j);
}

int	space_double_symbol(char *line, char *buffer, int count, int *i)
{
	buffer[count] = ' ';
	buffer[count + 1] = format_is_symbol(line[*i]);
	buffer[count + 2] = format_is_symbol(line[*i]);
	buffer[count + 3] = ' ';
	count += 4;
	(*i)++;
	return (count);
}

int	space_single_symbol(char *line, char *buffer, int count, int *i)
{
	buffer[count] = ' ';
	buffer[count + 1] = format_is_symbol(line[*i]);
	buffer[count + 2] = ' ';
	(*i)++;
	count += 3;
	return (count);
}
