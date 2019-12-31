NAME = cub3D

SRC = ft_gather_data.c\
	main.c

LIB = ft_printf/libftprintf.a

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OPENGL = -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit

all : $(NAME)
	make -C ft_printf/ re
	gcc -c -Wall -Werror -Wextra $(OPENGL) $(GNL) $(SRC)  $(LIB)  -o $(NAME)

clean:
	rm -f *.o ft_printf/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
