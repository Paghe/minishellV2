/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:31:21 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/17 16:13:53 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

int	unset_env_get(char ***envp, char *var_name, int sucess)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strnstr((*envp)[i], var_name, ft_strlen(var_name)) == (*envp)[i])
		{
			free((*envp)[i]);
			(*envp)[i] = (*envp)[i + 1];
			i++;
			while ((*envp)[i])
			{
				(*envp)[i] = (*envp)[i + 1];
				i++;
			}
			return (sucess = 1);
		}
		i++;
	}
	return (sucess);
}

char	*get_env_var(char *var_name, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0 \
				&& ft_strncmp(envp[i] + ft_strlen(var_name), "=", 1) == 0)
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

int	unset(char ***envp, char *var_name)
{
	int	i;
	int	sucess;

	i = 0;
	sucess = 0;
	if (!var_name)
		return (sucess);
	sucess = unset_env_get(envp, var_name, sucess);
	if (!sucess)
		EXIT_C = 1;
	return (sucess);
}

int	count_env_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

int	is_inside_env(char	**envp, char *var_name, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0 && \
				*(envp[i] + ft_strlen(var_name)) == '=')
			return (1);
		i++;
	}
	return (0);
}
