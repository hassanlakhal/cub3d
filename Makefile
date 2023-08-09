# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 16:31:00 by hlakhal-          #+#    #+#              #
#    Updated: 2023/08/09 20:46:54 by hlakhal-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c parssing_texture.c  parssing_utils.c free_list.c get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c\
		parssing_map.c

CC		= cc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

OBJ = $(SRCS:.c=.o)

all:cub3D

cub3D:$(OBJ)

		@make -sC libft/
		@$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit libft/libft.a  -o cub3D

clean:
		@make -sC libft/ clean
		@rm -f  $(OBJ)

fclean:	clean
		@make -sC libft/ fclean
		@rm -f $(NAME)

re:		fclean all
