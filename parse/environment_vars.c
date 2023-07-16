/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:59:13 by crepou            #+#    #+#             */
/*   Updated: 2023/07/16 21:19:55 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

extern char	**environ;

char	*ft_strdup2(const char *s1, int stop)
{
	char	*s2;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	if (!s1)
		return (0);
	s2 = malloc(sizeof (char) * len + 1);
	if (!s2)
		return (NULL);
	while (s1[i] != '\0' && i < stop)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*remove_spaces(char *str)
{
	char	**after;
	char	*tmp;
	int		i;
	char	*final;
	int		count;
	int		end_with_space;

	i = 0;
	if (!str)
		return (NULL);
	final = NULL;
	if (*str && *str == ' ')
		final = " ";
	after = ft_split(str, ' ');
	count = 0;
	while (str[i])
		i++;
	end_with_space = 0;
	if (str[i - 1] == ' ')
		end_with_space = 1;
	i = 0;
	while (after[count])
		count++;
	while (after[i])
	{
		final = ft_strjoin(final, after[i]);
		tmp = final;
		if (i < count - 1 || end_with_space)
		{
			final = ft_strjoin(final, " ");
			if (tmp)
				free(tmp);
			tmp = final;
		}
		i++;
	}
	return (final);
}

int	is_env_var(char *word, char	**var_name, char **value, char **env)
{
	char	*after_eq;
	int		index_bef_eq;

	if (*word == '?' || *(ft_strtrim(word, "\'\"")) == '=')
		return (0);
	after_eq = ft_strchr(word, '=');
	if (after_eq)
	{
		index_bef_eq = after_eq - word;
		(*value) = ft_strtrim((after_eq + 1), "\'\"");
		(*value) = remove_spaces(ft_strdup(*value));
		if ((*value) && (*value)[0] == '$')
			(*value) = get_env_var((*value) + 1, env);
		(*var_name) = ft_strdup2(word, index_bef_eq);
		return (1);
	}
	return (-1);
}

int	count_dollars(char *word)
{
	int	i;

	i = 0;
	if (!word)
		return (0);
	while (word && *word)
	{
		if (*word == '$')
			i++;
		else
			return (i);
		word++;
	}
	return (i);
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	if (envp)
		free(envp);
}
