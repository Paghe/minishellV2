/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:44:30 by crepou            #+#    #+#             */
/*   Updated: 2023/06/25 15:29:34 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

void	export(char **cmds, char ***env, char ***shell_env)
{
	char	*var_name;
	char	*value;
	int		is_var;

	var_name = NULL;
	value = NULL;
	is_var = is_env_var(cmds[1], &var_name, &value);
	if (is_var == 1)
	{
		set_env_var(env, var_name, value);
		set_env_var(shell_env, var_name, value);
		free(var_name);
		free(value);
	}
	else if (is_var == -1)
		return ;
	else
		printf("minishell: export: '%s': not a valid identifier\n", ft_strtrim(cmds[1], "\'\""));
}
