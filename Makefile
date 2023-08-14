# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 16:31:00 by hlakhal-          #+#    #+#              #
#    Updated: 2023/08/14 03:26:16 by hlakhal-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c parssing_texture.c  parssing_utils.c free_list.c get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c\
		parssing_map.c parssing_utils1.c parssing_utils2.c path_of_player.c raycatsing.c

CLANG		= clang

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

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

