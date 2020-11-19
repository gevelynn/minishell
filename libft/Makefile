FUNCTIONS_BASIS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c \
ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
get_next_line.c ft_free.c
FUNCTIONS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJECTS = $(FUNCTIONS_BASIS:.c=.o)
OBJECTS_BONUS = $(FUNCTIONS_BONUS:.c=.o)
FLAGS = -Wall -Werror -Wextra
CC = clang
HEADER = libft.h
NAME = libft.a

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $?
	@ranlib $(NAME)

%.o: %.c $(HEADER)
	@$(CC) -c $(FLAGS) $< -o $@

bonus: $(OBJECTS_BONUS) $(OBJECTS)
	@ar rc $(NAME) $?
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean:	clean
	@rm -rf $(NAME)

re: fclean all