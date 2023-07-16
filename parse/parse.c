/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:59:22 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 15:17:40 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

char	*escape_quote(char	*cmds)
{
	int		i;
	int		j;
	char	*new_cmds;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		if (cmds[i] != '\"' && cmds[i] != '\'')
			j++;
		i++;
	}
	new_cmds = malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (cmds[i])
	{
		if (cmds[i] && (cmds[i] != '\"' && cmds[i] != '\''))
			new_cmds[j++] = cmds[i];
		i++;
	}
	new_cmds[j] = '\0';
	return (new_cmds);
}

void	no_quote(t_cmds *cmds)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmds->cmds[i])
	{
		tmp = escape_quote(cmds->cmds[i]);
		if (cmds->cmds[i])
			free(cmds->cmds[i]);
		cmds->cmds[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}

t_token	*next_token(t_token *current)
{
	if (current)
	{
		current = current->next;
		return (current);
	}
	return (current);
}

void	add_cmds_env(t_cmds **cmds, char **envp, int i, int *j)
{
	cmds[i]->data.env = get_env_path(envp, cmds[i]->cmds[0]);
	(*j)++;
	cmds[i]->cmds[*j] = NULL;
}

void	parse_tokens(t_tokens *tokens, t_cmds **cmds, char **envp)
{
	t_token	*current;
	int		i;
	int		j;

	current = tokens->front;
	i = 0;
	j = 0;
	while (current)
	{
		current = handle_pipes(current, cmds, &i, &j);
		if (is_input_redirect(current))
			current = handle_input(current, cmds, i);
		else if (is_output_redirect(current))
			current = handle_output(current, cmds, i);
		else if (is_the_word(current) && \
					ft_strcmp(cmds[i]->data.input, current->token))
		{
			create_commands(cmds, current, i, j);
			add_cmds_env(cmds, envp, i, &j);
			current = next_token(current);
		}
		else
			current = next_token(current);
	}
}

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
		//if (cmds[i]->data.is_redir_first == 1)
		//{
		//	i++;
		//	continue ;
		//}
		if (cmds[i]->data.is_updated == 0)
		{
			while (cmds[i]->cmds[j] && cmds[i]->data.exist)
			{
				final = NULL;
				if ((ft_strnstr(cmds[i]->cmds[j], "-n", ft_strlen(cmds[i]->cmds[j]))) || is_assign(cmds[i]->cmds[j]))
				{
					//printf("hello\n");
					j++;
					continue ;
				}
				arg = ft_strdup(cmds[i]->cmds[j]);
				//char *new_var = replace_var(arg);
				int k = 0;
				//printf("COMMAND: %s start with dollar: %i\n", cmds[i]->cmds[j], cmds[i]->cmds[j][0] == '$');
				if (j > 0 || cmds[i]->cmds[j][0] == '$')
				{
					char *arg2= ft_strdup(arg);
					if (*arg2 == '?')
						arg2 = arg2 + 1;
					int sum = ft_strlen(arg2);
					while(sum > -1)
					{
						variable = next_var(arg2, arg2, &k);
						//printf("NEXT VAR: %s\n", variable);
						dollars = count_dollars(arg2);
						if (k == -1)
							break;
						sum -= k;
						arg2 = arg2 + k;
						new_val = get_next_var(variable, envp);
						//printf("new_val: %s\n", new_val);
						if (dollars % 2 != 0 && new_val != NULL)
						{
							cmds[i]->data.is_updated = 1;
							dollar_str = ft_strdup2(cmds[i]->cmds[j], dollars - 1);
							//free(cmds[i]->cmds[j]);
							char	*tmp = ft_strjoin(dollar_str, new_val);
							//printf("TMP: %s\n", tmp);
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
						//printf("replaced_command: %s\n", final);
						free(cmds[i]->cmds[j]);
						cmds[i]->cmds[j] = ft_strdup(final);
						k = 0;
					}
					if (new_val)
						free(new_val);
					//printf("AFTER: %s\n", cmds[i]->cmds[j]);
				}
				
				//else if (dollars % 2 == 0 && new_val != NULL)
				//{
				//	dollar_str = ft_strdup2(cmds[i]->cmds[j], dollars);
				//	printf("value: %s\n", new_val);
				//	free(cmds[i]->cmds[j]);
				//	cmds[i]->cmds[j] = ft_strjoin(dollar_str, new_val);
				//	printf("join: %s\n", cmds[i]->cmds[j]);
				//	free(dollar_str);
				//}
				if (arg)
					free(arg);
				j++;
			}	
		}
		i++;
	}
}
