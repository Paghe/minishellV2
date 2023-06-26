/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/26 14:30:26 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/control.h"
#include "include/parse.h"

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

int	execute(char **envp, int *exit_code)
{
	int		exec_code;
	t_lexer	lexer;
	t_cmds	**cmds;
	char	*input;
	char	**shell_env;

	// signal(SIGINT, cntr_handler);
	// signal(SIGQUIT, cntr_handler);
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
		replace_env_vars(cmds, envp);
		execute_cmds(cmds, &envp, &shell_env, \
						exit_code, count_commands(lexer.tokens));
		destroy_tokens(lexer.tokens);
		free_parse(cmds);
		if (*exit_code == -1)
			break ;
	}
/* 	free_env(shell_env);
	free_env(envp); */
	return (exec_code);
}

int	main(int argc, char **argv, char **envp)
{
	int		code;
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
