/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:17:49 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/16 21:22:42 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "lexer.h"
# include <sys/types.h>
# include <sys/wait.h>
# include "../gnl/get_next_line.h"

# define READ_END 0
# define WRITE_END 1

extern	int	EXIT_C;

typedef struct s_data
{
	char		*env;
	char		*input;
	char		*output;
	int			fd_in;
	int			fd_out;
	int			pipe_in;
	int			pipe_out;
	int			is_append;
	int			is_redir_first;
	int			is_updated;
	int			out_redir_first;
	int			exist;
}	t_data;

typedef struct s_cmds
{
	char	**cmds;
	t_data	data;
	int		flag;
}	t_cmds;

char	*escape_quote(char	*cmds);
void	no_quote(t_cmds *cmds);
int		is_symbol(t_token *token);
int		check_first_token(t_token	*token);
int		not_correct_pos(t_token *current);
int		get_grammar(t_tokens *tokens);
int		is_word(t_token *token);
t_token	*handle_input(t_token *current, t_cmds **cmds, int i);
t_token	*handle_output(t_token *current, t_cmds **cmds, int i);
void	create_commands(t_cmds **cmds, t_token *current, int i, int j);
t_token	*handle_pipes(t_token *current, t_cmds **cmds, int *i, int *j);
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
int		pipe_proccess(t_cmds **red, char ***envp, t_cmds **all, \
							int n_commands, char ***shell_env);
int		is_env_var(char *word, char	**var_name, char **value, char **env);
char	*get_env_var(char *var_name, char **envp);
void	replace_env_vars(t_cmds **cmds, char **envp);
int		count_dollars(char *word);
char	**escape_quotes_cmds(char **cmds);
int		unset(char ***envp, char *var_name);
void	print_env(char **envp);
int		set_env_var(char ***envp, char	*var_name, char *value);
void	free_env(char **envp);
int		if_is_builtin(char *cmd);
int		is_echo_newline(char *current);
int		only_echo(t_cmds **cmds);
int		built_in(t_cmds *cmds, char ***env, char ***shell_envp, int *exit);
int		if_is_exit(t_cmds *cmds, int flag, int *exit);
int		exit_format(int i, t_cmds *cmds, int flag, int *exit);
int		echo(t_cmds *cmds);
int		change_dir(char **env, t_cmds *cmds);
int		go_to_user(t_cmds *cmds, char *dir, char **env);
void	change_old(char **env);
char	*get_path(t_cmds *cmds);
void	change_current_pwd(char **env);
char	*go_home(char **env);
int		get_env(t_cmds *cmds, char **env);
int		build_pwd(t_cmds *cmds);
int		pwd_goes_void(char **env, t_cmds *cmds);
int		is_void_pwd(t_cmds *cmds);
int		count_env_vars(char **envp);
void	export(char **cmds, char ***env, char ***shell_env);
int		unset_env_get(char ***envp, char *var_name, int sucess);
char	*ft_strdup2(const char *s1, int stop);
void	here_doc(t_token *token, t_cmds *cmds);
char	*get_next_var(char *var, char **envp);
char	*remove_char_from_word(char *str, char c);
char	*put_dollar_back(char *str);
char	*next_var(char *str, char	*real_str, int *i);

#endif