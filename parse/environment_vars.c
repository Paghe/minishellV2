/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:59:13 by crepou            #+#    #+#             */
/*   Updated: 2023/06/20 13:23:56 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

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

int	is_env_var(char *word, char	**var_name, char **value)
{
	char	*after_eq;
	int		index_bef_eq;

	after_eq = ft_strchr(word, '=');
	if (after_eq)
	{
		index_bef_eq = after_eq - word;
		(*value) = ft_strdup(after_eq + 1);
		(*var_name) = ft_strdup2(word, index_bef_eq);
		return (1);
	}
	return (0);
}

//char	*get_env_var(char *var_name)
//{
//	char	*value;

//	value = getenv(var_name);
//	if (value)
//		return (value);
//	value = "";
//	return (value);
//}

int	count_dollars(char *word)
{
	int	i;

	i = 0;
	if (!word)
		return (0);
	while (*word)
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
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
