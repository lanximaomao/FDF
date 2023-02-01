NAME = fdf
SRCS = line.c map_handeling.c image_handeling.c hooks.c clean.c color.c isometric.c draw.c conversion.c main.c
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft all
	make -C libft bonus
	cc $(FLAGS) $(SRCS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) libft/libft.a

clean:
	make -C ./libft clean

fclean: clean
	make -C ./libft fclean
	rm $(NAME);

re: fclean all

.PHONY: all clean fclean re libft
