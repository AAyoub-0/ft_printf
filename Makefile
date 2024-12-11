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

$(NAME): $(LIBFT) $(OBJ) $(HEAD)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ) $(LIBFT)
# $(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

./%.o: ./%.c $(HEAD) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
