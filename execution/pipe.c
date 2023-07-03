/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:49:01 by crepou            #+#    #+#             */
/*   Updated: 2023/07/04 00:30:16 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/control.h"
#include "../include/parse.h"

extern char	**environ;

int	init_pipes(t_cmds **cmds, int index)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	cmds[index]->data.pipe_out = pipe_fd[WRITE_END];
	if (cmds[index + 1])
		cmds[index + 1]->data.pipe_in = pipe_fd[READ_END];
	return (0);
}

void	close_all(t_cmds **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->data.pipe_in != -1)
			close(cmds[i]->data.pipe_in);
		if (cmds[i]->data.pipe_out != -1)
			close(cmds[i]->data.pipe_out);
		// if (cmds[i]->data.fd_in != -1)
		// 	printf("fd in: %i\n", cmds[i]->data.fd_in);
		// if (cmds[i]->data.fd_out != -1)
		// 	printf("fd out: %i\n", cmds[i]->data.fd_out);
		i++;
	}
}

void	pipe_proccess(t_cmds **red, char ***envp, t_cmds **all , int n_commands, char ***shell_env)
{
	int	pid;

	(void)all;
	if (!(*red)->data.is_redir_first && if_is_builtin((*red)->cmds[0]) && n_commands ==  1)
	{
		built_in(*red, envp, shell_env);
		if ((*red)->data.pipe_in != -1)
			close((*red)->data.pipe_in);
		if ((*red)->data.pipe_out != -1)
			close((*red)->data.pipe_out);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("pipe_process\n");
		return ;
	}
	if (pid == 0)
	{
		if (!(*red)->data.is_redir_first && (*red)->data.env == NULL)
		  {
			char *tmp;
			char *tmp2;
			tmp = ft_strjoin("minishell: ",(*red)->cmds[0]);
			tmp2 = ft_strjoin(tmp, ": No such file or directory");
			ft_putendl_fd(tmp2, 2);
			free(tmp);
			free(tmp2);
			exit(0);
		  }
    if (!(*red)->data.is_redir_first && if_is_builtin((*red)->cmds[0]))
    {
    	built_in(*red, envp, shell_env);
		exit(0);
    }
    else
    {
      if ((*red)->data.pipe_in != -1)
        dup2((*red)->data.pipe_in, READ_END);
      if ((*red)->data.pipe_out != -1)
        dup2((*red)->data.pipe_out, WRITE_END);
      close_all(all);
      if ((*red)->data.input || (*red)->data.output)
      {
        (*red)->data.fd_in = open((*red)->data.input, O_RDONLY);
        if ((*red)->data.is_append)
          (*red)->data.fd_out = open((*red)->data.output, O_WRONLY | O_APPEND | O_CREAT, 0644);
        else
          (*red)->data.fd_out = open((*red)->data.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        redirect_io((*red)->data.fd_in, (*red)->data.fd_out);
        close((*red)->data.fd_in);
        close((*red)->data.fd_out);
      }
		  if ((*red)->data.is_redir_first)
		  {
			char	*tmp[3] = {"/usr/bin/echo", "-n", NULL};
			if (execve("/usr/bin/echo", tmp, *envp) == -1)
				exit(0);
		  }
		  (*red)->cmds = escape_quotes_cmds((*red)->cmds);
		 if (ft_strncmp((*red)->cmds[0], "./", 2) == 0)
			{
				if (execve((*red)->cmds[0], (*red)->cmds, *envp) == -1)
				{
					char *tmp = ft_strjoin("minishell: ", (*red)->cmds[0]);
					char *tmp2 = ft_strjoin(tmp, ": command not found");
					ft_putendl_fd(tmp2, 2);
					free(tmp);
					free(tmp2);
					exit(-1);
				}
			}
			else
			{
				if (execve((char const *)(*red)->data.env, (*red)->cmds, *envp) == -1)
				{
					char *tmp = ft_strjoin("minishell: ", (*red)->cmds[0]);
					char *tmp2 = ft_strjoin(tmp, ": command not found");
					ft_putendl_fd(tmp2, 2);
					free(tmp);
					free(tmp2);
					exit(-1);
				}
			}
		}
	}
	if ((*red)->data.pipe_in != -1)
		close((*red)->data.pipe_in);
	if ((*red)->data.pipe_out != -1)
		close((*red)->data.pipe_out);
	waitpid(pid, NULL, 0);
}
