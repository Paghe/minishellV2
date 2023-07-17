/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:49:01 by crepou            #+#    #+#             */
/*   Updated: 2023/07/17 15:01:14 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		i++;
	}
}

void	free_everything(t_cmds **red, char ***envp, \
							char ***shell_env, t_tokens *tokens)
{
	free_env(*envp);
	free_env(*shell_env);
	free_parse(red);
	destroy_tokens(tokens);
}
void	value_exit(int e_code)
{
	EXIT_C = e_code;
	if (e_code == 255)
		EXIT_C = 127;
	if (e_code == 126)
		EXIT_C = 126;
	if (e_code == 1)
		EXIT_C = 1;
	if (e_code == 0)
		EXIT_C = 0;
}
int	wait_process(int last_pid, int last)
{
	int	exit;
	int	status;
	int	e_code;

	exit = 0;
	e_code = 0;
	while (exit != -1)
	{
		exit = waitpid(-1, &status, 0);
		if (exit == last_pid)
			e_code = WEXITSTATUS(status);
	}
	if (last != -2)
		value_exit(e_code);
	if (last == -1 || last == -2)
		return (1);
	else
		return (0);
}

int	pipe_proccess(t_cmds **red, char ***envp, t_cmds **all, int n_commands, char ***shell_env, t_tokens *tokens)
{
	int	pid;
	int	exit_st;
	int	stdin_terminal;
	int	stdout_terminal;

	exit_st = 0;
	if ((*red)->data.exist && if_is_builtin((*red)->cmds[0]) && n_commands ==  1)
	{
		stdout_terminal = dup(STDOUT_FILENO);
		stdin_terminal = dup(STDIN_FILENO);
		if ((*red)->data.input || (*red)->data.output)
		{
			(*red)->data.fd_in = open((*red)->data.input, O_RDONLY);
			if ((*red)->data.is_append)
				(*red)->data.fd_out = open((*red)->data.output, O_WRONLY | O_APPEND | O_CREAT, 0644);
			else
				(*red)->data.fd_out = open((*red)->data.output, O_WRONLY);
			redirect_io((*red)->data.fd_in, (*red)->data.fd_out);
		}
		EXIT_C = 0;
		built_in(*red, envp, shell_env, &exit_st);
		redirect_io(stdin_terminal, stdout_terminal); 
		if ((*red)->data.pipe_in != -1)
			close((*red)->data.pipe_in);
		if ((*red)->data.pipe_out != -1)
			close((*red)->data.pipe_out);
		return (exit_st);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("pipe_process\n");
		return (exit_st);
	}
	if (pid == 0)
	{
    if ((*red)->data.exist && if_is_builtin((*red)->cmds[0]))
    {
		if ((*red)->data.input || (*red)->data.output)
		{
			(*red)->data.fd_in = open((*red)->data.input, O_RDONLY);
			if ((*red)->data.is_append)
				(*red)->data.fd_out = open((*red)->data.output, O_WRONLY | O_APPEND | O_CREAT, 0644);
			else
				(*red)->data.fd_out = open((*red)->data.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			redirect_io((*red)->data.fd_in, (*red)->data.fd_out);
		}
		built_in(*red, envp, shell_env, &exit_st);
		free_everything(red, envp, shell_env, tokens);
		exit(exit_st);
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
      }
		if ((*red)->cmds)
			(*red)->cmds = escape_quotes_cmds((*red)->cmds);
		 if ((*red)->cmds[0] && ft_strncmp((*red)->cmds[0], "./", 2) == 0)
			{
				if (execve((*red)->cmds[0], (*red)->cmds, *envp) == -1)
				{
					char *tmp;
					char *tmp2;
					if (!access((*red)->cmds[0] + 2, F_OK) && access((*red)->cmds[0] + 2, X_OK) != 0)
					{
						tmp = ft_strjoin("minishell: ", (*red)->cmds[0]);
						tmp2 = ft_strjoin(tmp, ": Permission denied");
					}
					else
					{
						tmp = ft_strjoin("minishell: ", (*red)->cmds[0]);
						tmp2 = ft_strjoin(tmp, ": command not found");
						
					}
					ft_putendl_fd(tmp2, 2);
					free(tmp);
					free(tmp2);
					if (!access((*red)->cmds[0] + 2, F_OK) && access((*red)->cmds[0] + 2, X_OK) != 0)
					{
						free_everything(red, envp, shell_env, tokens);
						exit (126);
					}
					free_everything(red, envp, shell_env, tokens);
					exit(-1);
				}
			}
			else
			{
				if (execve((char const *)(*red)->data.env, (*red)->cmds, *envp) == -1)
				{
					char *tmp;
					char *tmp2;
					tmp = ft_strjoin("minishell: ", (*red)->cmds[0]);
					tmp2 = ft_strjoin(tmp, ": command not found");
					ft_putendl_fd(tmp2, 2);
					free(tmp);
					free(tmp2);
					free_everything(red, envp, shell_env, tokens);
					exit(-1);
				}
			}
		}
	}
	if ((*red)->data.pipe_in != -1)
		close((*red)->data.pipe_in);
	if ((*red)->data.pipe_out != -1)
		close((*red)->data.pipe_out);
	if ((*red)->data.fd_in != -1)
		close((*red)->data.fd_in);
	if ((*red)->data.fd_out != -1)
		close((*red)->data.fd_out);
	return (pid);
}
