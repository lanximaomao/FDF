NAME = fdf
SRCS = my_main.c
OBJS = $(SRCS:.c=.o)
#INCLUDE = libft/libft.h
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C ./libft all
	make -C ./libft bonus
	cc -I /usr/local/include -L /usr/local/lib $(FLAGS) $(SRCS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) 
	#cc $(FLAGS) $(SRCS) -lmlx -lXext -lX11 -o $(NAME) -L . ./libft/libft.a

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm $(NAME);

re: fclean all

.PHONY: all clean fclean re libft
