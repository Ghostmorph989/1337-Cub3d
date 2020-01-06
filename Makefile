NAME =	cub3D.a

SRC =	ft_gather_data.c\
		ft_wall_casting.c\
		main.c

LIB =	ft_printf/libftprintf.a

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OPENGL =   -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : 
		make -C ft_printf/ re
		gcc -c  -Wall -Werror -Wextra  $(SRC)
		ar rc $(NAME) *.o 
		ranlib $(NAME)

clean:
	rm -f *.o ft_printf/*.o minilibx/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
