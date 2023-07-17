/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:27:05 by crepou            #+#    #+#             */
/*   Updated: 2023/07/17 16:10:51 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

extern char	**environ;

int	get_env_index(char	**envp, char	*var_name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0 && \
				ft_strncmp(envp[i] + ft_strlen(var_name), "=", 1) == 0)
			return (i);
		i++;
	}
	return (i);
}

char	**envp_memory_alloc(char ***envp, char *var_name, int count)
{
	char	**new_envp;

	new_envp = NULL;
	if (is_inside_env(*envp, var_name, count))
		new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	else
		new_envp = (char **)malloc(sizeof(char *) * (count + 2));
	return (new_envp);
}

char	**get_new_env(char **new_envp, char ***envp, int *i, int count)
{
	while (*i < count)
	{
		new_envp[*i] = ft_strdup((*envp)[*i]);
		free((*envp)[*i]);
		(*i)++;
	}
	return (new_envp);
}

char	**get_inside_env(char **new_envp, char *var_name, char *value, int j)
{
	char	*temp;

	temp = NULL;
	j = get_env_index(new_envp, var_name);
	free(new_envp[j]);
	temp = ft_strjoin(var_name, "=");
	new_envp[j] = ft_strjoin(temp, value);
	free(temp);
	return (new_envp);
}

int	set_env_var(char ***envp, char	*var_name, char *value)
{
	char	**new_envp;
	int		i;
	int		j;
	int		count;
	char	*temp;

	i = 0;
	j = 0;
	count = count_env_vars(*envp);
	new_envp = envp_memory_alloc(envp, var_name, count);
	if (!new_envp)
		return (0);
	new_envp = get_new_env(new_envp, envp, &i, count);
	if (is_inside_env(new_envp, var_name, count))
		new_envp = get_inside_env(new_envp, var_name, value, j);
	else
	{
		temp = ft_strjoin(var_name, "=");
		new_envp[i++] = ft_strjoin(temp, value);
		free(temp);
	}
	new_envp[i] = NULL;
	free(*envp);
	*envp = new_envp;
	return (1);
}
