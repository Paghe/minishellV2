/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:27:05 by crepou            #+#    #+#             */
/*   Updated: 2023/07/16 21:17:28 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

extern char	**environ;

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

int	is_inside_env(char	**envp, char	*var_name, int count)
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
	if (is_inside_env(*envp, var_name, count))
		new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	else
		new_envp = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (0);
	while (i < count)
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		free((*envp)[i]);
		i++;
		j++;
	}
	if (is_inside_env(new_envp, var_name, count))
	{
		j = get_env_index(new_envp, var_name);
		free(new_envp[j]);
		temp = ft_strjoin(var_name, "=");
		new_envp[j] = ft_strjoin(temp, value);
		free(temp);
	}
	else
	{
		temp = ft_strjoin(var_name, "=");
		new_envp[i] = ft_strjoin(temp, value);
		free(temp);
		i++;
	}
	new_envp[i] = NULL;
	free(*envp);
	*envp = new_envp;
	return (1);
}
