/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:31:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/10 22:57:58 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define PATH 1
# define RGB 2

typedef struct s_bloc
{
	char		*val_1;
	char		*val_2;
	int			type;
	int			bloc_size_texteur;
	int			bloc_size_rgb;
}				t_bloc;

typedef struct s_rgb_info
{
	char		*type_color;
	char		*rgb_value;
	int			_R;
	int			_G;
	int			_B;
}				t_rgb_info;

typedef struct s_texteur
{
	char		*path;
	char		*direction;
}				t_texteur;

typedef struct s_general
{
	t_rgb_info	*info_rgb;
	t_texteur	*info_texteur;
	t_bloc		*bloc_s;
	char		*bloc;
	char		*map;
	int			number_of_line;

}				t_general;

void			free_2d(char **tab);
void			get_map(t_general *info);


t_general	*ft_parssing_map(t_general *data);
void			read_lines_texter(t_general *info);
void			ft_bloc(t_general *data, t_bloc *data_of_texture);
int				ft_strlen_2d(char **tab);
t_general		*ft_parssing(void);
void			clear_all(t_general *data, int a, int b);
char			**ft_split_pos(char *str, char c, int pos);
char			*skip_line(int fd);
char			*reaplace(char *text, int number, char c);
void			check_direction(t_bloc *data_of_texture);
void			check_line(char **tab, int a);

#endif
