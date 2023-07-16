/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:46:36 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 21:01:56 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

char	*replace_var(char *var)
{
	char	*prev;
	char	*curr;
	char	*next;

	prev = var;
	curr = var;
	next = var + 1;
	while (curr && next && *curr && *next)
	{
		if (*prev == '\"' && *curr == '$' && *next == '\"')
			*curr = 17;
		else if (*prev == '\'' && *curr == '$' && *next == '\'')
			*curr = 17;
		prev = curr;
		curr = next;
		next++;
	}
	return (var);
}

char	*put_dollar_back(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == 17)
			str[i] = '$';
		i++;
	}
	return (str);
}

char	*next_dollar(char *str)
{
	int		i;
	int		is_code_var;
	char	*new_var;
	char	*tmp;

	i = -1;
	is_code_var = 0;
	while (str && str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			is_code_var = 1;
			break ;
		}
	}
	new_var = ft_strdup2(str, i);
	tmp = new_var;
	if (is_code_var)
	{
		new_var = ft_strjoin(tmp, ft_itoa(EXIT_C));
		new_var = ft_strjoin(tmp, str + 3);
		free(tmp);
	}
	return (new_var);
}

int	is_assign(char *str)
{
	int	index_first_quote;
	int	index_first_eq;
	int	i;

	index_first_quote = 0;
	index_first_eq = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			index_first_quote = i;
			break ;
		}
		if (str[i] == '=')
		{
			index_first_eq = i;
			break ;
		}
		i++;
	}
	if (index_first_eq > index_first_quote)
		return (1);
	else
		return (0);
}

void	replace_env_vars(t_cmds **cmds, char **envp)
{
	int		i;
	int		j;
	char	*arg;
	int		dollars;
	char	*dollar_str;
	char	*new_val;
	char	*variable;
	char	*final;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		if (cmds[i]->data.is_updated == 0)
		{
			while (cmds[i]->cmds[j] && cmds[i]->data.exist)
			{
				final = NULL;
				if ((ft_strnstr(cmds[i]->cmds[j], "-n", ft_strlen(cmds[i]->cmds[j]))) || is_assign(cmds[i]->cmds[j]))
				{
					j++;
					continue ;
				}
				arg = ft_strdup(cmds[i]->cmds[j]);
				int k = 0;
				if (j > 0 || cmds[i]->cmds[j][0] == '$')
				{
					char *arg2= ft_strdup(arg);
					if (*arg2 == '?')
						arg2 = arg2 + 1;
					int sum = ft_strlen(arg2);
					while (sum > -1)
					{
						variable = next_var(arg2, arg2, &k);
						dollars = count_dollars(arg2);
						if (k == -1)
							break ;
						sum -= k;
						arg2 = arg2 + k;
						new_val = get_next_var(variable, envp);
						if (dollars % 2 != 0 && new_val != NULL)
						{
							cmds[i]->data.is_updated = 1;
							dollar_str = ft_strdup2(cmds[i]->cmds[j], dollars - 1);
							char	*tmp = ft_strjoin(dollar_str, new_val);
							final = ft_strjoin(final, tmp);
							free(dollar_str);
						}
						if (!new_val)
						{
							variable = remove_char_from_word(variable, '\"');
							char *tmp = put_dollar_back(variable);
							variable = next_dollar(tmp);
							final = ft_strjoin(final, variable);
						}
						free(cmds[i]->cmds[j]);
						cmds[i]->cmds[j] = ft_strdup(final);
						k = 0;
					}
					if (new_val)
						free(new_val);
				}
				if (arg)
					free(arg);
				j++;
			}	
		}
		i++;
	}
}
