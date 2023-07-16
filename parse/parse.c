/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:59:22 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 21:31:06 by crepou           ###   ########.fr       */
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
		{
			new_cmds[j] = cmds[i];
			j++;
		}
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

int	count_commands(t_tokens	*tokens)
{
	t_token	*current;
	int		count;

	count = 1;
	current = tokens->front;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void	parse_tokens(t_tokens *tokens, t_cmds **cmds, char **envp)
{
	t_token	*current;
	int		i;
	int		j;
	int		fd;
	int		flag;

	current = tokens->front;
	i = 0;
	j = 0;
	flag = 1;
	while (current)
	{
		if (current->type == PIPE)
		{
			flag = 0;
			init_pipes(cmds, i);
			i++;
			current = current->next;
			j = 0;
		}
		if (is_input_redirect(current))
		{
			if (current->type == DLESS)
			{
				current = current->next;
				if (cmds[i]->data.input)
					free(cmds[i]->data.input);
				cmds[i]->data.input = ft_strdup("temp_file");
				here_doc(current, cmds[i]);
				if (current->next && is_the_word(current->next))
					current = current->next;
				else
					break ;
			}
			if ((current->type == LESS) && (current->next && is_the_word(current->next)))
			{
				if (cmds[i]->data.input)
					free(cmds[i]->data.input);
				cmds[i]->data.input = ft_strdup(current->next->token);
				if (current->next && is_the_word(current->next))
					current = current->next;
			}
			if (flag == 1)
				cmds[i]->data.is_redir_first = 1;
		}
		if (is_output_redirect(current))
		{
			if (flag == 1)
				cmds[i]->data.is_redir_first = 1;
			if (current->type == DMORE)
				cmds[i]->data.is_append = 1;
			if (current->next && is_the_word(current->next))
			{
				if (cmds[i]->data.output)
					free(cmds[i]->data.output);
				cmds[i]->data.output = ft_strdup(current->next->token);
				if (cmds[i]->data.is_append)
					fd = open(current->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					fd = open(current->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				close(fd);
				current = current->next;
				if (current->next && is_the_word(current->next))
					cmds[i]->data.exist = 1;
			}
		}
		else
		{
			flag = 0;
			if (cmds[i]->data.env)
				free(cmds[i]->data.env);
			cmds[i]->cmds[j] = ft_strdup(current->token);
			cmds[i]->data.exist = 1;
			char *tmp = ft_strtrim(cmds[i]->cmds[0], "\"");
			if (cmds[i]->cmds[0])
				free(cmds[i]->cmds[0]);
			cmds[i]->cmds[0] = ft_strdup(tmp);
			free(tmp);
			cmds[i]->data.env = get_env_path(envp, cmds[i]->cmds[0]);
			j++;
			cmds[i]->cmds[j] = NULL;
		}
		if (current)
		{
			flag = 0;
			current = current->next;
		}
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
			*curr =  17;
		else if (*prev == '\'' && *curr == '$' && *next == '\'')
			*curr =  17;
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
		if (str[i] ==  17)
			str[i] = '$';
		i++;
	}
	return (str);
}

char	*next_dollar(char *str)
{
	int	i;
	int	is_code_var;
	char	*new_var;
	char	*tmp;
	
	i = -1;
	is_code_var = 0;
	while (str && str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			is_code_var = 1;
			break;
		}
	}
	new_var = ft_strdup2(str, i);
	tmp = new_var;
	if (is_code_var)
	{
		new_var = ft_strjoin(tmp, ft_itoa(EXIT_C));
		//printf("NEW VAR2: %shello STR2: %s\n", new_var, str + i + 2);
		//tmp = new_var;
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
	char	*tmp_variable;
	char	*tmp_arg;
	char	*tmp_final;
	char	*tmp_commands;

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
				tmp_arg = arg;
				int k = 0;
				if (j > 0 || cmds[i]->cmds[j][0] == '$')
				{
					if (*arg == '?')
						arg = arg + 1;
					int sum = ft_strlen(arg);
					tmp_commands = cmds[i]->cmds[j];
					while(sum > -1)
					{
						variable = next_var(arg, arg, &k);
						dollars = count_dollars(arg);
						if (k == -1)
							break;
						sum -= k;
						arg = arg + k;
						new_val = get_next_var(variable, envp);
						if (dollars % 2 != 0 && new_val != NULL)
						{
							cmds[i]->data.is_updated = 1;
							dollar_str = ft_strdup2(cmds[i]->cmds[j], dollars - 1);
							char	*tmp = ft_strjoin(dollar_str, new_val);
							tmp_final = final;
							final = ft_strjoin(final, tmp);
							if (tmp_final)
								free(tmp_final);
							if (tmp)
								free(tmp);
							free(dollar_str);
						}
						if (!new_val)
						{
							tmp_variable = variable;
							variable = remove_char_from_word(variable, '\"');
							if (tmp_variable)
								free(tmp_variable);
							tmp_variable = variable;
							char *tmp = put_dollar_back(variable);
							variable = next_dollar(tmp);
							if (tmp_variable)
								free(tmp_variable);
							tmp_final = final;
							final = ft_strjoin(final, variable);
							if (tmp_final)
								free(tmp_final);
						}
						else
						{
							if (new_val)
								free(new_val);
						}
						if (variable)
							free(variable);
						if (tmp_commands)
							free(tmp_commands);
						cmds[i]->cmds[j] = ft_strdup(final);
						tmp_commands = cmds[i]->cmds[j];
						k = 0;
					}
					if (final)
						free(final);
				}
				if (tmp_arg)
					free(tmp_arg);
				j++;
			}	
		}
		i++;
	}
}

void	free_parse(t_cmds **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i]->cmds && cmds[i]->cmds[j])
		{
			if (cmds[i]->data.exist)
				free(cmds[i]->cmds[j]);
			j++;
		}
		if (cmds[i]->cmds)
			free(cmds[i]->cmds);
		if (cmds[i]->data.env)
			free(cmds[i]->data.env);
		if (cmds[i]->data.input)
			free(cmds[i]->data.input);
		if (cmds[i]->data.output)
			free(cmds[i]->data.output);
		free(cmds[i]);
		i++;
	}
}
