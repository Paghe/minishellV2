CC = gcc
CFLAGS  = -Wall -Wextra -Werror
NAME = libft.a
cd = ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isascii.c ft_isprint.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
	ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c 

bonus_obj = ft_lstadd_back.c ft_lstadd_front.c ft_lstdelone.c ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

obj = $(cd:.c=.o)
bobj = $(bonus_obj:.c=.o)

all: $(NAME)

test: test.c $(NAME)
	$(CC) $(CFLAGS) test.c $(NAME) -o test


$(NAME): $(obj)
	ar rcs $(NAME) $(obj)

$(obj) : $(cd)
	$(CC) -c $(CFLAGS) ${cd}

bonus: $(obj) $(bobj)
	ar rcs $(NAME) $(obj) $(bobj)

$(bobj) : $(bonus_obj)
	$(CC) -c $(CFLAGS) ${bonus_obj}

fclean: clean
	$(RM) -f $(NAME)

clean: 
	$(RM) -f $(obj) $(bobj)

re: fclean all