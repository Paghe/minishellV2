/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:15:51 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/03 17:09:59 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

/* void	execute_cmd(t_cmds *cmds, char **envp)
{
	pid_t	pid;

	cmds->data.fd_in = open(cmds->data.input, O_RDONLY);
	cmds->data.fd_out = open(cmds->data.output, O_WRONLY | \
								O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		redirect_io(cmds->data.fd_in, cmds->data.fd_out);
		close(cmds->data.fd_in);
		close(cmds->data.fd_out);
		execve(cmds->data.env, cmds->cmds, envp);
	}
	else
		waitpid(pid, NULL, 0);
	return ;
}

void execute_cmds(t_cmds **cmds, char ***envp, char ***shell_env, int *exit_code, int n_commands)
{
	int		i;
	char	*var_name;
	char	*value;

	i = 0;
	var_name = NULL;
	value = NULL;
	while (cmds[i])
	{
		if (ft_strncmp(cmds[i]->cmds[0], "exit", 4) == 0)
		{
			*exit_code = -1;
			return ;
		}
		if (ft_strncmp(cmds[i]->cmds[0], "export", 6) == 0)
			export(cmds[i]->cmds, envp, shell_env);
		else if (ft_strncmp(cmds[i]->cmds[0], "unset", 5) == 0)
		{
			unset(envp, cmds[i]->cmds[1]);
			unset(shell_env, cmds[i]->cmds[1]);
		}
		else if (is_env_var(cmds[i]->cmds[0], &var_name, &value))
		{
			set_env_var(shell_env, var_name, value);
			free(var_name);
			free(value);
		}
		else
			pipe_proccess(&cmds[i], *envp, cmds, n_commands);
		if (cmds[i]->data.env)
			free(cmds[i]->data.env);
		i++;
	}
}
 */