/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../include/cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:31:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/24 14:12:57 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include "../mlx_Linux/mlx.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#define PATH 1
#define RGB 2
#define PI 3.141592653
#define RAD 0.0174533
#define HEIGHT 700
#define WIDTH 1500
#define SPEED 0.1
#define SPEEDALPHA 2

typedef struct s_coordinates
{
	double i;
	double j;

} t_coordinates;

typedef struct s_bloc
{
	char *val_1;
	char *val_2;
	int type;
	int bloc_size_texteur;
	int bloc_size_rgb;
} t_bloc;

typedef struct s_rgb_info
{
	char *type_color;
	char *rgb_value;
	int _R;
	int _G;
	int _B;
} t_rgb_info;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	char direction;
} t_player;

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_data;

typedef struct s_texteur
{
	char *path;
	char *direction;
	t_data *texteur;
} t_texteur;

typedef struct s_casted_ray
{
	t_coordinates end;
	double lenght;
} t_casted_ray;

typedef struct s_drawing
{
	float x;
	float y;
	double k;
	double i;
	double d;
	float x_crement;
	float y_crement;

} t_drawing;

typedef struct s_general
{
	t_rgb_info *info_rgb;
	t_texteur *info_texteur;
	t_player *info_player;
	t_bloc *bloc_s;
	t_data *info_img;
	t_data *texteur;
	t_data *mini_map;
	t_casted_ray *v;
	t_casted_ray *h;
	t_coordinates *start;
	t_coordinates *end;
	char *name_map;
	char **valid_map;
	int dimensions[2];
	char *bloc;
	char *map;
	int number_of_line;
	void *mlx;
	void *mlx_win;
	double alpha;
	double bita_ray;
	double wall_hight;
} t_general;

void free_2d(char **tab);
void get_map(t_general *info);
/* parssing */
void	utils_get_map(char *str, int fd); 
void	get_map(t_general *info);
void	check_dobule_new_line(char *str);
void	check_wall(char **str, int y);

int	ft_block_rgb(t_rgb_info *bloc_2);
void	valid_format_1(char c, bool *intoken, int *digit);
void	valid_format_2(int intoken, int *digit, int *token);
bool	valid_format(const char *input);
void	cont_of_coma(char *rgb);
void	ft_fill_info_1(t_bloc *line, t_general *info_bloc);
void	ft_fill_info_2(t_bloc *line, t_general *info_bloc);
void	ft_fill_info(t_bloc *line, t_general *info_bloc);
void	ft_bloc(t_general *data, t_bloc *data_of_texture);
int	ft_block_texteurs(t_texteur *bloc_1);
void	type_of_bloc(t_bloc *lines);
void	utils_reaplace(char *result, char *text, int number, char c);
int	get_max_of_line(char **map);

t_general *ft_parssing_map(t_general *data);
void read_lines_texter(t_general *info);
void ft_bloc(t_general *data, t_bloc *data_of_texture);
int ft_strlen_2d(char **tab);
t_general *ft_parssing(int ac, char **av);
void clear_all(t_general *data, int a, int b);
char **ft_split_pos(char *str, char c, int pos);
char *skip_line(int fd);
char *reaplace(char *text, int number, char c);
void check_direction(t_bloc *data_of_texture);
void check_line(char **tab, int a);
void framing_map(char **map, char **dup_map);
void floodfile(char **map, t_general info);
int rgbToHex(int red, int green, int blue);
/* raycasting */
void display_pixel(t_general info);
int draw_rays(t_general *info);
void ft_mini_map(t_general *info, void *mlx, void *mlx_win);
void	my_mlx_pixel_put(t_general *info, int x, int y, int color);
int	draw_line(t_general *info);
void	calcule_bite_ray(t_general *info);

void	my_mlx_pixel_put(t_general *info, int x, int y, int color);
int	my_mlx_get_pixel(t_data *texteur, int x, int y);
void	move_up(t_general *info, t_data *img);
void	move_down(t_general *info, t_data *img);
void	move_left(t_general *info, t_data *img);
void	move_right(t_general *info, t_data *img);

void	draw_help_1(t_general *info, double *i, double *d);
void	draw_help(t_general *info, t_data *texteur, int steps, double img_x);
void	sub_draw_line(t_general *info, double endi, t_data *texteur);

void	display_floor(t_general *info, t_data *img, int j, int i);
void	display_sky(t_general *info, t_data *img, int j, int i);
void	ft_dislay(t_general *info, void *mlx, void *mlx_win);
int	draw_line(t_general *info);
void	draw_texteur(t_general *info);

void	rotate_right(t_general *info);
void	rotate_left(t_general *info);

t_casted_ray	*horizontal(t_general *info, double beta);
t_casted_ray	*vertecal(t_general *info, double beta);

bool	break_wall(t_general *info, int x, int y);
void	step_rays(t_general *info, double *x_steps, double *y_steps,
		double beta);
void	set_len(t_general *info, t_casted_ray *h);
void	step_rays_v(t_general *info, double *x_steps, double *y_steps,
		double beta);
double	calcule_projection(t_general *info);
void	calcule_of_wall(t_general *info, int i, t_coordinates *start);
t_data	*get_side_texteur(t_general *info, char *str);
int	get_color(t_general *info, char c);
void	calcule_bite_ray(t_general *info);
double	get_alpha_player(t_general info);
void	get_texters(t_general *info);

#endif
