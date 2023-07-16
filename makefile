FLAGS = -Wall -Wextra -Werror #-I $(shell brew --prefix readline)/include
#FLAGS += -g -fsanitize=address 

NAME = minishell

SRC = main.c \
	lexer/lexer.c	\
	lexer/lex_utils.c	\
	lexer/lex_utils_two.c \
	utils/init_link_lst.c \
	utils/util.c \
	utils/token_utils.c \
	builtin/echo.c \
	builtin/cd.c \
	builtin/cd_utils.c \
	builtin/env.c \
	builtin/pwd.c \
	builtin/utils_builtin.c \
	builtin/built.c \
	parse/parse.c	\
	parse/grammar.c	\
	parse/utils_parse.c \
	parse/utils_parse_two.c \
	parse/init_parse.c \
	control_commands/control.c \
	execution/redirection_utils.c \
	execution/input_redirection.c \
	execution/output_redirection.c \
	parse/utils_redir.c \
	execution/pipe.c \
	execution/heredoc.c \
	parse/environment_vars.c \
	builtin/unset.c \
	builtin/export.c \
	execution/execution.c \
	parse/env_vars_check.c

OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a
GNL = ./gnl/libgnl.a

LINKFLAGS = -lreadline  #-L/Users/apaghera/Documents/LeakSanitizer -llsan -lc++ #-L$(shell brew --prefix readline)/lib

all: 
	$(MAKE) $(NAME) -j

%.o: %.c
	gcc $(FLAGS) -c $^ -o $@

$(NAME): $(OBJ) include/lexer.h
	make -C libft
	gcc  $(OBJ) $(LIBFT) $(GNL) -o $(NAME) $(LINKFLAGS) $(FLAGS) 
clean:
	rm -f $(OBJ)
	make clean -C libft
	make clean -C gnl

fclean:
	make clean
	rm -f $(NAME)
	rm -f $(LIBFT)

test:
	@cd tests && bash tester.sh a

re: fclean all
