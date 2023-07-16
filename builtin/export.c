/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:44:30 by crepou            #+#    #+#             */
/*   Updated: 2023/07/16 20:04:34 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

void	error_message_export(char *tmp, char **cmds)
{
	tmp = ft_strtrim(cmds[1], "\'\"");
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	ft_putstr_fd(": not a valid identifier", 2);
}

void	export(char **cmds, char ***env, char ***shell_env)
{
	char	*var_name;
	char	*value;
	int		is_var;
	char	*tmp;

	var_name = NULL;
	value = NULL;
	is_var = 0;
	tmp = NULL;
	if (cmds && cmds[1])
		is_var = is_env_var(cmds[1], &var_name, &value, *shell_env);
	if (is_var == 1)
	{
		set_env_var(env, var_name, value);
		set_env_var(shell_env, var_name, value);
		free(var_name);
	}
	else if (is_var == -1)
		return ;
	else
	{
		EXIT_C = 1;
		if (cmds && cmds[1])
			error_message_export(tmp, cmds);
	}
}
