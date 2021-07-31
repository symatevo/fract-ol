NAME = fractol

SRC = srcs/fractol.c\
	  srcs/mandelbrot.c\
	  srcs/julia.c\

OBJ = *.o

HEADERS = includes/fractol.h\

LIBFT = libft/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

MLX = -lmlx -framework OpenGL -framework AppKit
all: $(NAME)

$(NAME):
	@${MAKE} -C libft
	@$(CC) $(FLAGS) -c $(SRC) -I$(HEADERS)
	@$(CC) $(FLAGS) $(MLX) -o $(NAME) $(OBJ) $(LIBFT)
	@mkdir obj
	@mv $(OBJ) ./obj

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -Rf obj
	@${MAKE} -C libft clean

fclean: clean
	@/bin/rm -f $(NAME)
	@${MAKE} -C libft fclean

re: fclean all

.PHONY: all clean fclean re

