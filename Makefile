NAME =	cub3D

SRC =	ft_gather_data.c\
		ft_intersection.c\
		ft_wall_casting.c\
		main.c


LIB =	ft_printf/libftprintf.a

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

Flags = -Wall -Werror -Wextra

OPENGL =  -framework OpenGL -framework AppKit

MLIB = minilibx/libmlx.a

all : $(NAME)

$(NAME) : 
		make -C ft_printf/ re
		make -C minilibx/ re
		gcc  -o $(NAME) $(GNL) $(SRC) $(MLIB) $(LIB) $(OPENGL) -g

clean:
	rm -f *.o ft_printf/*.o minilibx/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
