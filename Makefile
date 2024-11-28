NAME = libftprintf.a

HEAD = libftprintf.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC = ft_printf.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $(OBJ)

./%.o: ./%.c $(HEAD) Makefile
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
