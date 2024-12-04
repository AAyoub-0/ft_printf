NAME = libftprintf.a

HEAD = ft_printf.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = 	ft_printf.c \
	ft_printf_utils.c \
	flags.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEAD) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ)
# $(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)


./%.o: ./%.c $(HEAD) Makefile $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
