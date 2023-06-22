/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/21 21:20:56 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/control.h"
#include "include/parse.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	execute_cmd(t_cmds *cmds, char **envp)
{
	pid_t	pid;

	cmds->data.fd_in = open(cmds->data.input, O_RDONLY);
	cmds->data.fd_out = open(cmds->data.output, O_WRONLY | O_CREAT | O_TRUNC, 0644); // opening here file doesn't matter the order
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		redirect_io(cmds->data.fd_in, cmds->data.fd_out); // dup2(input, STDIN_FILENO); // dup2(output, STDOUT_FILENO);												 // dup2(output, STDOUT_FILENO);
		close(cmds->data.fd_in);
		close(cmds->data.fd_out);
		execve(cmds->data.env, cmds->cmds, envp);
	}
	else
		waitpid(pid, NULL, 0);
	return ;
}

char	**copy_env(char **envp)
{
	char	**new_envp;
	int		i;
	int		count;

	i = 0;
	count = count_env_vars(envp);
	new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

void	execute_cmds(t_cmds **cmds, char ***envp, char ***shell_env, int *exit_code, int n_commands)
{
	int		i;
	// char	*var_name;
	// char	*value;
	// int		fd_in;
	// int		fd_out;
	(void)n_commands;
	i = 0;
	// fd_in = dup(STDIN_FILENO);
	// fd_out = dup(STDOUT_FILENO);
	// var_name = NULL;
	// value = NULL;
	(void)shell_env;
	(void)exit_code;
	while (cmds[i])
	{
		// if (ft_strncmp(cmds[i]->cmds[0], "unset", 5) == 0)
		// 	unset(envp, cmds[i]->cmds[1]);
		// if (cmds[i]->data.pipe_in != -1)
		// 	dup2(cmds[i]->data.pipe_in, READ_END);
		// if (cmds[i]->data.pipe_out != -1)
		// 	dup2(cmds[i]->data.pipe_out, WRITE_END);
		// if (cmds[i]->data.input || cmds[i]->data.output)
		// {
		// 	cmds[i]->data.fd_in = open(cmds[i]->data.input, O_RDONLY);
		// 	// if (cmds[i]->data.is_append)
		// 		// cmds[i]->data.fd_out = open(cmds[i]->data.output, O_WRONLY | O_APPEND | O_CREAT, 0644);
		// 	// else
		// 		cmds[i]->data.fd_out = open(cmds[i]->data.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// 	redirect_io(cmds[i]->data.fd_in, cmds[i]->data.fd_out);
		// 	close(cmds[i]->data.fd_in);
		// 	close(cmds[i]->data.fd_out);
		// }
		// if (is_env_var(cmds[i]->cmds[0], &var_name, &value))
		// {
		// 	//if (setenv(var_name, value, 1) == -1)
		// 	//	perror("setenv");
		// 	set_env_var(envp, var_name, value);
		// 	free(var_name);
		// 	free(value);
		// }
		// else if (if_is_builtin(cmds[i]->cmds[0]))
		// {
		// built_in(cmds[i], *envp);

		// }
		// else
			pipe_proccess(&cmds[i], *envp, cmds, n_commands);
		//execute_cmd(cmds[i], envp); // execute multiple cmds;
		if (cmds[i]->data.env)
			free(cmds[i]->data.env);
		i++;
	}
	// close_all(cmds);
	// dup2(fd_in, STDIN_FILENO); 
	// dup2(fd_out, STDOUT_FILENO);
	//while (j != i - 1) //save status of last
	//{
	//	waitpid(struct pid, NULL, 0);
	//	j++;
	//}
}

int	execute(char **envp, int *exit_code)
{
	int		exec_code;
	t_lexer	lexer;
	t_cmds	**cmds;
	char	*input;
	char **shell_env;

	signal(SIGINT, cntr_handler);
	signal(SIGQUIT, cntr_handler);
	cmds = NULL;
	exec_code = 0;
	shell_env = copy_env(envp);
	while (1)
	{
		clear_line();
		input = readline("minishell 🚀 ");
		if (!input)
		{
			exec_code = -1;
			break ;
		}
		if (input && input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		parsing(&lexer, ft_strdup(input));
		free(input);
		if (!get_grammar(lexer.tokens))
		{
			destroy_tokens(lexer.tokens);
			return (0);
		}
		cmds = init_list_commands(lexer.tokens);
		parse_tokens(lexer.tokens, cmds, envp);
		// replace_env_vars(cmds, envp);
		execute_cmds(cmds, &envp, &shell_env, exit_code, count_commands(lexer.tokens));
		destroy_tokens(lexer.tokens);
		free_parse(cmds);
	}
	free_env(shell_env);
/* 	free_env(envp); */
	return (exec_code);
}

int	main(int argc, char **argv, char **envp)
{
	int	code;
	char	**env_vars;
	int		exit_code;
	
	errno = 0;
	exit_code = 0;
	env_vars = copy_env(envp);
	(void)argc;
	(void)argv;
	if ((code = execute(env_vars, &exit_code)) == -1)
	{
		free_env(env_vars);
		return (-1);
	}
	free_env(env_vars);
	return (0);
}
