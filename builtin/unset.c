/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:27:05 by crepou            #+#    #+#             */
/*   Updated: 2023/06/20 12:55:03 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("ENVP[%i]: %s\n", i, envp[i]);
		i++;
	}
}

int	unset(char ***envp, char *var_name)
{
	int	i;
	int	sucess;

	i = 0;
	sucess = 0;
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
			sucess = 1;
			break ;
		}
		i++;
	}
	return (sucess);
}

int	count_env_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	set_env_var(char ***envp, char	*var_name, char *value) //fix protection
{
	char	**new_envp;
	int		i;
	int		count;
	char	*temp;

	i = 0;
	count = count_env_vars(*envp);
	new_envp = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (0);
	while (i < count)
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		i++;
	}
	temp = ft_strjoin(var_name, "=");
	new_envp[i] = ft_strjoin(temp, value);
	free(temp);
	i++;
	new_envp[i] = NULL;
	*envp = new_envp;
	return (1);
}

char	*get_env_var(char *var_name, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0)
			return (ft_strrchr(envp[i], '=') + 1);
		i++;
	}
	return ("");
}
