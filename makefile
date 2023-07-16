FLAGS = -Wall -Wextra -Werror -g#-I $(shell brew --prefix readline)/include
ifdef DEBUG 
FLAGS += -g -fsanitize=leak
else
# FLAGS += -g -fsanitize=address
endif

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

LINKFLAGS = -lreadline #-g -L/Users/crepou/Documents/LeakSanitizer  #-fsanitize=leak#-L/Users/crepou/Documents/LeakSanitizer -llsan -lc++ #-L$(shell brew --prefix readline)/lib
ifdef DEBUG
LINKFLAGS += -g -fsanitize=leak
else
# LINKFLAGS += -g -fsanitize=address
endif

all: 
	$(MAKE) $(NAME) -j

%.o: %.c
	gcc $(FLAGS) -c $^ -o $@

$(NAME): $(OBJ) include/lexer.h
	make -C libft
	make -C gnl
	gcc  $(OBJ) $(LIBFT) $(GNL) -o $(NAME) $(LINKFLAGS) $(FLAGS) 
clean:
	rm -f $(OBJ)
	make clean -C libft
	make clean -C gnl

fclean:
	make clean
	rm -f $(NAME)
	$(MAKE) -C gnl fclean
	rm -f $(LIBFT)

test:
	@cd tests && bash tester.sh a

re: fclean all
