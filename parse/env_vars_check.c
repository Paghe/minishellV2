/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:12:06 by crepou            #+#    #+#             */
/*   Updated: 2023/07/12 20:20:33 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

int	EXIT_C;

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
		if (start[i][0] ==  '?')
			return (ft_strdup(ft_itoa(EXIT_C)));
		if (start[i][0] != '\"')
		{
			final = ft_strjoin(final, get_env_var(start[i], envp));
			if (tmp)
				free(tmp);
			tmp = final;
		}
		else
		{
			final = ft_strjoin(final, ft_strtrim(start[i], "\""));
			if (tmp)
				free(tmp);
			tmp = final;
		}
		i++;
	}
	return (final);
}
