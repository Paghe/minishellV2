/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/25 18:00:06 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/control.h"
#include "include/parse.h"
#include "gnl/get_next_line.h"

void leaks(void)
{
	system("leaks minishell");
}

void execute_cmd(t_cmds *cmds, char **envp)
{
	pid_t pid;

	cmds->data.fd_in = open(cmds->data.input, O_RDONLY);
	cmds->data.fd_out = open(cmds->data.output, O_WRONLY | O_CREAT | O_TRUNC, 0644); // opening here file doesn't matter the order
	pid = fork();
	if (pid == -1)
		return;
	if (pid == 0)
	{
		redirect_io(cmds->data.fd_in, cmds->data.fd_out); // dup2(input, STDIN_FILENO); // dup2(output, STDOUT_FILENO);												 // dup2(output, STDOUT_FILENO);
		close(cmds->data.fd_in);
		close(cmds->data.fd_out);
		execve(cmds->data.env, cmds->cmds, envp);
	}
	else
		waitpid(pid, NULL, 0);
	return;
}

char **copy_env(char **envp)
{
	char **new_envp;
	int i;
	int count;

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

void execute_cmds(t_cmds **cmds, char ***envp, char ***shell_env, int *exit_code, int n_commands)
{
	int		i;
	char	*var_name;
	char	*value;
	(void)n_commands;
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

int execute(char **envp, int *exit_code)
{
	int exec_code;
	t_lexer lexer;
	t_cmds **cmds;
	char *input;
	char **shell_env;

	// signal(SIGINT, cntr_handler);
	// signal(SIGQUIT, cntr_handler);
	cmds = NULL;
	exec_code = 0;
	shell_env = copy_env(envp);
	while (1)
	{
		clear_line();
		// if (isatty(STDIN_FILENO))
			input = readline("minishell 🚀 ");
		// else
			// input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			exec_code = -1;
			break;
		}
		if (input && input[0] == '\0')
		{
			free(input);
			continue;
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
		replace_env_vars(cmds, envp);
		replace_env_vars(cmds, shell_env);
		execute_cmds(cmds, &envp, &shell_env, exit_code, count_commands(lexer.tokens));
		destroy_tokens(lexer.tokens);
		free_parse(cmds);
		if (*exit_code == -1)
			break;
	}
	free_env(shell_env);
		free_env(envp);
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
	if ((code = execute(envp, &exit_code)) == -1)
	{
		free_env(env_vars);
		return (-1);
	}
	free_env(env_vars);
	return (0);
}
