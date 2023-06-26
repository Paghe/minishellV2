/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:17:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/26 14:18:54 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "lexer.h"
//  #include <sys/types.h>
//   #include <sys/wait.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_data
{
	char		*env;
	char		*input;
	char		*output;
	int			fd_in;
	int			fd_out;
	int			pipe_in;
	int			pipe_out;
}	t_data;

typedef struct s_cmds
{
	char	**cmds;
	t_data	data;
}	t_cmds;

char	*escape_quote(char	*cmds);
void	no_quote(t_cmds *cmds);
int		is_symbol(t_token *token);
int		check_first_token(t_token	*token);
int		get_grammar(t_tokens *tokens);
int		is_word(t_token *token);
void	parse_tokens(t_tokens *tokens, t_cmds **cmds, char **envp);
int		is_input_redirect(t_token *token);
int		is_output_redirect(t_token *token);
int		is_the_word(t_token *token);
int		count_commands(t_tokens	*tokens);
t_cmds	**init_list_commands(t_tokens *tokens);
void	free_parse(t_cmds **cmds);
void	input_redirection(t_cmds **red, char **envp);
void	output_redirection_renew(t_cmds **red, char **envp);
void	redirect_io(int input, int output);
int		begin_with_pipes(t_token *token);
int		init_pipes(t_cmds **cmds, int index);
void	close_all(t_cmds **cmds);
void	pipe_proccess(t_cmds **red, char **envp, t_cmds **all , int n_commands);
int		is_env_var(char *word, char	**var_name, char **value);
char	*get_env_var(char *var_name, char **envp);
void	replace_env_vars(t_cmds **cmds, char **envp);
int		count_dollars(char *word);
char	**escape_quotes_cmds(char **cmds);
int		unset(char ***envp, char *var_name);
void	print_env(char **envp);
int		set_env_var(char ***envp, char	*var_name, char *value);
void	free_env(char **envp);
int		built_in(t_cmds *cmds, char **env);
int		if_is_builtin(char *cmd);
int		echo(t_cmds *cmds);
int		change_dir(char **env, t_cmds *cmds);
void	change_old(char **env);
char	*get_path(t_cmds *cmds);
void	change_current_pwd(char **env);
char	*go_home(char **env);
int		get_env(t_cmds *cmds, char **env);
int		build_pwd(t_cmds *cmds);
int		pwd_goes_void(char **env, t_cmds *cmds);
int		count_env_vars(char **envp);
void	export(char **cmds, char ***env, char ***shell_env);
void	execute_cmd(t_cmds *cmds, char **envp);
void	execute_cmds(t_cmds **cmds, char ***envp, char ***shell_env, int *exit_code, int n_commands);
#endif