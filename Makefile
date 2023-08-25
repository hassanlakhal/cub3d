NAME = cub3D

SRCS = main.c \
		utils/free_list.c \
		get_next_line/get_next_line.c  \
		get_next_line/get_next_line_utils.c\
		parssing/parssing_texture.c  \
		parssing/parssing_utils.c \
		parssing/parssing_map_utils_1.c \
		parssing/parssing_map.c \
		parssing/parssing_utils1.c \
		parssing/parssing_utils2.c \
		parssing/path_of_player.c \
		parssing/parssing_texture_utils_1.c \
		parssing/parssing_texture_utils_2.c \
		parssing/parssing_texture_utils_3.c \
		raycasting/raycasting.c \
		raycasting/rgb_to_hexa.c \
		raycasting/mini_map.c \
		raycasting/mlx_utils.c \
		raycasting/moves.c \
		raycasting/display.c \
		raycasting/rotate.c \
		raycasting/draw.c \
		raycasting/rays.c \
		raycasting/texters.c \
		raycasting/rays_utils.c \
		raycasting/raycasting_utils.c \



CLANG		=  clang

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

OBJ = $(SRCS:.c=.o)

all:cub3D

%.o: %.c
	$(CLANG) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@


cub3D:$(OBJ)

		@make -sC libft/
		@$(CLANG) $(CFLAGS) $(OBJ) -pedantic  -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz libft/libft.a  -o cub3D

clean:
		@make -sC libft/ clean
		@rm -f  $(OBJ)

fclean:	clean
		@make -sC libft/ fclean
		@rm -f $(NAME)

re:		fclean all

