/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:53:59 by apaghera          #+#    #+#             */
/*   Updated: 2023/06/25 16:23:07 by apaghera         ###   ########.fr       */
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

#endif