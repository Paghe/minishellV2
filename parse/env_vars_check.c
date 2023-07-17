/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:12:06 by crepou            #+#    #+#             */
/*   Updated: 2023/07/17 16:26:25 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

int	EXIT_C;

int	count_char_in_word(char *str, char c)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

char	*remove_char_from_word(char *str, char c)
{
	int		count;
	int		i;
	char	*new_str;

	count = ft_strlen(str) - count_char_in_word(str, c);
	if ((size_t) count == ft_strlen(str))
	{
		count = ft_strlen(str) - count_char_in_word(str, '\'');
		c = '\'';
	}
	new_str = (char *)malloc(count + 1);
	i = 0;
	while (i < count)
	{
		if (*str == c)
		{
			str++;
			continue ;
		}
		new_str[i] = *str;
		i++;
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*next_var(char *str, char	*real_str, int *i)
{
	char	quote_type;
	char	*new_var;
	int		has_dollar;

	quote_type = 17;
	has_dollar = 0;
	if (real_str && *real_str && (*real_str == '\"' || *real_str == '\'' || *real_str == '$'))
	{
		if (real_str && *real_str && *real_str == '$')
		{
			has_dollar = 1;
			(real_str)++;
			(*i)++;
		}
		if (real_str && *real_str && (*real_str) == '\"')
		{
			quote_type = '\"';
			(real_str)++;
			(*i)++;
		}
		else if (real_str && *real_str && (*real_str) == '\'')
		{
			quote_type = '\'';
			(real_str)++;
			(*i)++;
		}
		if (quote_type != 17)
		{
			while (real_str && *real_str && *real_str != quote_type)
			{
				(real_str)++;
				(*i)++;
			}
		}
		else
		{
			while (real_str && *real_str)
			{
				if (*real_str == '\"' || *real_str == '\'' || *real_str == '$')
				{
					(*i)--;
					(real_str)--;
					break ;
				}
				(real_str)++;
				(*i)++;
			}
		}
		(*i)++;
	}
	else
	{
		while (real_str && *real_str)
		{
			if (*real_str == '\"' || *real_str == '\'' || *real_str == '$')
			{
				(*i)--;
				(real_str)--;
				break ;
			}
			(real_str)++;
			(*i)++;
		}
		(*i)++;
	}
	new_var = ft_strdup2(str, (real_str) - str + 1);
	return (new_var);
}

char	*get_next_var(char *var, char **envp)
{
	char	**start;
	char	*tmp;
	char	*final;
	int		i;
	int		is_var;

	is_var = 0;
	if (!var)
		return (NULL);
	if (*var == '$')
		is_var = 1;
	else
		return (NULL);
	start = ft_split(var, '$');
	i = 0;
	tmp = NULL;
	final = NULL;
	while (start[i])
	{
		if (start[i][0] == '?')
			final = ft_strjoin(final, ft_itoa(EXIT_C));
		else if (start[i][0] != '\"' && start[i][0] != '\'')
		{
			final = ft_strjoin(final, get_env_var(start[i], envp));
			if (tmp)
				free(tmp);
			tmp = final;
		}
		else
		{
			char *after_trim = remove_char_from_word(start[i], '\"');
			final = ft_strjoin(final, after_trim);
			final = put_dollar_back(final);
			free(after_trim);
			if (tmp)
				free(tmp);
			tmp = final;
		}
		free(start[i]);
		i++;
	}
	free(start);
	return (final);
}
