NAME = cub3D

SRCS =  mandatory/main.c \
        mandatory/utils/free_list.c \
        get_next_line/get_next_line.c  \
        get_next_line/get_next_line_utils.c\
        mandatory/parssing/parssing_texture.c  \
        mandatory/parssing/parssing_utils.c \
        mandatory/parssing/parssing_map_utils_1.c \
        mandatory/parssing/parssing_map.c \
        mandatory/parssing/parssing_utils1.c \
        mandatory/parssing/parssing_utils2.c \
        mandatory/parssing/path_of_player.c \
        mandatory/parssing/parssing_texture_utils_1.c \
        mandatory/parssing/parssing_texture_utils_2.c \
        mandatory/parssing/parssing_texture_utils_3.c \
        mandatory/raycasting/raycasting.c \
        mandatory/raycasting/rgb_to_hexa.c \
        mandatory/raycasting/mlx_utils.c \
        mandatory/raycasting/moves.c \
        mandatory/raycasting/display.c \
        mandatory/raycasting/rotate.c \
        mandatory/raycasting/draw.c \
        mandatory/raycasting/rays.c \
        mandatory/raycasting/texters.c \
        mandatory/raycasting/rays_utils.c \
        mandatory/raycasting/key_hooks.c \
        mandatory/raycasting/raycasting_utils.c \

SRCS_BONUS =  bonus/main.c \
        bonus/utils/free_list.c \
        get_next_line/get_next_line.c  \
        get_next_line/get_next_line_utils.c\
        bonus/parssing/parssing_texture.c  \
        bonus/parssing/parssing_utils.c \
        bonus/parssing/parssing_map_utils_1.c \
        bonus/parssing/parssing_map.c \
        bonus/parssing/parssing_utils1.c \
        bonus/parssing/parssing_utils2.c \
        bonus/parssing/path_of_player.c \
        bonus/parssing/parssing_texture_utils_1.c \
        bonus/parssing/parssing_texture_utils_2.c \
        bonus/parssing/parssing_texture_utils_3.c \
        bonus/raycasting/raycasting.c \
        bonus/raycasting/rgb_to_hexa.c \
        bonus/raycasting/mini_map.c \
        bonus/raycasting/mlx_utils.c \
        bonus/raycasting/moves.c \
        bonus/raycasting/display.c \
        bonus/raycasting/rotate.c \
        bonus/raycasting/draw.c \
        bonus/raycasting/rays.c \
        bonus/raycasting/texters.c \
        bonus/raycasting/rays_utils.c \
        bonus/raycasting/key_hooks.c \
        bonus/raycasting/raycasting_utils.c \

CLANG        = cc
CFLAGS = -Wall -Wextra -Werror

MLX = -lmlx -lXext -lX11 -lm 

OBJ = $(SRCS:.c=.o)

OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all:cub3D

%.o: %.c
		$(CLANG) $(CFLAGS) -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

cub3D:$(OBJ)
		@make -sC libft/
		@$(CLANG) $(CFLAGS) $(OBJ) -pedantic  -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz libft/libft.a  -o cub3D


bonus:$(OBJ_BONUS)
	@make -sC libft/
	@$(CLANG) $(CFLAGS) $(OBJ_BONUS) -pedantic  -Lmlx_Linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz libft/libft.a  -o cub3D

clean:
		@make -sC libft/ clean
		@rm -f  $(OBJ)
		@rm -f  $(OBJ_BONUS)

fclean:    clean
		@make -sC libft/ fclean
		@rm -f $(NAME)

re:        fclean all