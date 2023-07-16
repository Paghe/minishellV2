/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:12:06 by crepou            #+#    #+#             */
/*   Updated: 2023/07/16 18:33:10 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

//int	quotes_around_dollar(char )

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

	quote_type = 17;
	if (real_str && *real_str && (*real_str == '\"' || *real_str == '\'' || *real_str == '$'))
	{
		if (real_str && *real_str && *real_str == '$')
		{
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
			//	if (quote_type == '\'')
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
	char	*final;
	int		i;

	if (!var)
		return (NULL);
	if (*var != '$')
		return (NULL);
	start = ft_split(var, '$');
	i = 0;
	final = NULL;
	while (start[i])
	{
		if (start[i][0] ==  '?')
		{
			char	*num_tmp = ft_itoa(EXIT_C);
			char *tmp2 = NULL;
			tmp2 = ft_strjoin(final, num_tmp);
			free(final);
			final = ft_strdup(tmp2);
			free(tmp2);
			free(num_tmp);
		}
		else if (start[i][0] != '\"' && start[i][0] != '\'')
		{
			char *tmp2 = NULL;
			tmp2 =  ft_strjoin(final, get_env_var(start[i], envp));
			free(final);
			final = ft_strdup(tmp2);
			free(tmp2);
		}
		else
		{
			char *tmp2 = NULL;
			char *after_trim = remove_char_from_word(start[i], '\"');
			tmp2 = ft_strjoin(final, after_trim);
			free(final);
			final = ft_strdup(tmp2);
			free(tmp2);
			final = put_dollar_back(final);
			free(after_trim);
		}
		free(start[i]);
		i++;
	}
	free(start);
	return (final);
}
