NAME = cub3D

SRCS = main.c parssing/parssing_texture.c  parssing/parssing_utils.c utils/free_list.c get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c\
		parssing/parssing_map.c parssing/parssing_utils1.c parssing/parssing_utils2.c parssing/path_of_player.c raycasting/raycasting.c raycasting/rgb_to_hexa.c raycasting/mini_map.c

CLANG		=  clang

CFLAGS = -Wall -Wextra -Werror  -g3 -fsanitize=address

OBJ = $(SRCS:.c=.o)

all:cub3D

%.o: %.c
	$(CLANG) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@


cub3D:$(OBJ)

		@make -sC libft/
		@$(CLANG) $(CFLAGS) $(OBJ) -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz libft/libft.a  -o cub3D

clean:
		@make -sC libft/ clean
		@rm -f  $(OBJ)

fclean:	clean
		@make -sC libft/ fclean
		@rm -f $(NAME)

re:		fclean all

