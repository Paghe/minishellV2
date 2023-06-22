/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:20:03 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/07 17:30:00 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

char	format_is_symbol(char symbol)
{
	if (symbol == '<' || symbol == '>' || symbol == '|')
		return (symbol);
	return (0);
}
