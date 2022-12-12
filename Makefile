all:
	cc my_main.c -lmlx -framework OpenGL -framework AppKit



#NAME = libftprintf.a
#SRCS = ft_printf.c ft_hexa_deci.c ft_printf_ptr.c ft_printf_utils.c
#OBJS = $(SRCS:.c=.o)
#INCLUDE = libft/libft.h
#CFLAGS = -c -Wall -Wextra -Werror

#all: $(NAME)

#$(NAME):
#	make -C ./libft all
#	make -C ./libft bonus
#	mv ./libft/libft.a ./$(NAME)
#	cc $(CFLAGS) $(SRCS) -I $(INCLUDE)
#	ar -rus $(NAME) $(OBJS)

#clean:
#	make -C ./libft clean
#	rm -f $(OBJS) $(BONUS_OBJS)

#fclean: clean
#	make -C ./libft fclean
#	rm -f $(NAME)
#	rm -f libft.a

#re: fclean all

#.PHONY: all clean fclean re libft
