/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:53:59 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/03 19:47:17 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define LINEBUFFER_MAX 4096

typedef struct s_token	t_token;

typedef enum e_token_type
{
	WORD,
	DQUOTE,
	SQUOTE,
	DMORE,
	DLESS,
	LESS,
	MORE,
	PIPE,
	DOLLAR,
}			t_token_type;

typedef struct s_token
{
	char			*token;
	t_token			*next;
	t_token_type	type;
}	t_token;

typedef struct s_tokens
{
	t_token	*front;
	t_token	*rear;
	size_t	size;
}	t_tokens;

typedef struct s_lexer
{
	int			argc;
	char		*input;
	t_tokens	*tokens;
}	t_lexer;

t_tokens	*create_tokens(void);
t_token		*new_token(char *format);
void		add_token(t_tokens *tokens, char *format, char *type);
int			ms_whitespace(char input);
void		parsing(t_lexer *lexer, char *input);
void		remove_token(t_token *tokens);
void		destroy_tokens(t_tokens *tokens);
void		def_type_tok(t_token *token);
void		print_token_type(t_token_type type);
void		print_token(t_tokens *tokens);
char		format_is_symbol(char symbol);
int			skip_whitespaces(char *str);
int			give_a_space(char *buffer, int j);
int			space_double_symbol(char *line, char *buffer, int count, int *i);
int			space_single_symbol(char *line, char *buffer, int count, int *i);
int			if_is_builtin(char *cmd);
void		tokenize_input_init(t_lexer *lexer, char *buffer, \
						char *good_line, char *buf_ptr);
char		*replace_spaces(char *str);
char		*format_line(char *line);
int			min(int a, int b);
void		token_parse(t_lexer *lexer, char *buffer, \
						char *good_line, char *buf_ptr);
int			have_dquote(char current, int squote, int dquote);
int			have_squote(char current, int squote, int dquote);
void		destroy_node(t_token *token);
void		destroy_tokens(t_tokens *tokens);

#endif