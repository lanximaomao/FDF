NAME = fdf
SRCS = line.c map_handeling.c image_handeling.c hooks.c clean.c color.c isometric.c draw.c conversion.c
SRCSDEST = $(addprefix ./SRCS/, $(SRCS))
FLAGS = -Wall -Wextra -Werror
MLX = -lmlx -framework OpenGL -framework AppKit
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(SRCSDEST) main.c includes/fdf.h
	make -C libft all
	make -C libft bonus
	cc $(FLAGS) $(SRCSDEST) -o $(NAME) $(LIB) $(MLX) main.c

clean:
	make -C ./libft clean

fclean: clean
	make -C ./libft fclean
	rm $(NAME);

re: fclean all

.PHONY: all clean fclean re libft
