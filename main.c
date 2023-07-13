/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/13 12:54:40 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parse.h"
#include "gnl/get_next_line.h"
#include "include/control.h"

extern char **environ;
int EXIT_C;

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
	new_envp[i] = NULL;
	return (new_envp);
}

int execute_cmds(t_cmds **cmds, char ***envp, char ***shell_env, int n_commands)
{
	int		i;
	char	*var_name;
	char	*value;
	int		exit;

	(void)n_commands;
	i = 0;
	var_name = NULL;
	value = NULL;
	exit = 0;
	while (cmds[i] && cmds[i]->data.exist)
	{
		//if (!cmds[i]->data.is_redir_first && ft_strlen(cmds[i]->cmds[0]) == 1 && *(cmds[i]->cmds[0]) == '.')
		//{
		//	ft_putendl_fd("minishell: .: filename argument required\n.: usage: . filename [arguments]", 2);
		//	i++;
		//	continue;
		//}
		//if (!cmds[i]->data.is_redir_first && is_env_var(cmds[i]->cmds[0], &var_name, &value) == 1)
		//{
		//	set_env_var(shell_env, var_name, value);
		//	free(var_name);
		//	free(value);
		//}
		//else
			exit = pipe_proccess(&cmds[i], envp, cmds, n_commands, shell_env);
		if (cmds[i]->data.env)
			free(cmds[i]->data.env);
		i++;
		if (exit == 15)
			break ;
	}
	return (exit);
}

void	check_redir(t_cmds **cmds)
{
	int		i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->data.is_redir_first == 1)
		{
			free(cmds[i]->cmds);
			cmds[i]->cmds[0] = NULL;
		}
		i++;
	}
}

int execute(char **envp)
{
	t_lexer lexer;
	t_cmds **cmds;
	char *input;
	char **shell_env;
	int		exit;

	cmds = NULL;
	shell_env = copy_env(envp);
	exit = 0;
	while (1)
	{
		signal(SIGINT, cntr_handler);
		signal(SIGQUIT, cntr_handler);
		clear_line();
		if (isatty(STDIN_FILENO))
			input = readline("minishell 🚀 ");
		else
			input = ft_strtrim(get_next_line(STDIN_FILENO), "\n");
		if (!input)
		{
			break;
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
			EXIT_C = 2;
		else
		{
			cmds = init_list_commands(lexer.tokens);
			parse_tokens(lexer.tokens, cmds, envp);
			replace_env_vars(cmds, envp);
			//replace_env_vars(cmds, shell_env);
			block_signals();
			exit = execute_cmds(cmds, &envp, &shell_env, count_commands(lexer.tokens));
			free_parse(cmds);
		}
		destroy_tokens(lexer.tokens);
		if (exit)
			break ;
	}
	free_env(shell_env);
	free_env(envp);
	return (EXIT_C);
}

int	main(int argc, char **argv, char **envp)
{
	int		code;
	char	**env_vars;

	errno = 0;
	EXIT_C = 0;
	env_vars = copy_env(envp);
	(void)argc;
	(void)argv;
	if ((code = execute(env_vars)) == -1)
		EXIT_C = -1;
	//EXIT_C = 0;
	//printf("exit code: %i\n", EXIT_C);
	return (EXIT_C);
}
