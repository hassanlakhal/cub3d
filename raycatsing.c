/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/18 10:04:33 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void sub_draw_line(t_general *info, t_coordinates *start, t_coordinates *end, int color)
{

	int dx = (end->i - start->i);
	int dy = (end->j - start->j);
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float xIncrement = (float)dx / (float)steps;
	float yIncrement = (float)dy / (float)steps;
	float x = start->i;
	float y = start->j;
	
	for (int i = 0; i <= steps; i++)
	{
		mlx_pixel_put(info->mlx, info->mlx_win, round(x), round(y), color);
		x += xIncrement;
		y += yIncrement;
	}
}


void display_player(double x, double y, t_data *img, int color)
{
	x *= 45;
	y *= 45;

	my_mlx_pixel_put(img, (int)x, (int)y, color);
}

void display_pxl(t_general *info, t_data *img, int j, int i)
{
	int y;
	int x;

	y = 0;
	while (y < info->dimensions[1])
	{
		x = 0;
		while (x < info->dimensions[0])
		{
			if (info->valid_map[y][x] == '1')
				my_mlx_pixel_put(img, (x * 45) + j, (y * 45) + i, 0x00FF0000);
			if (info->valid_map[y][x] == '0')
				my_mlx_pixel_put(img, (x * 45) + j, (y * 45) + i, 0x00FFFFFF);
			if (ft_strchr("NEWS", info->valid_map[y][x]))
			{
				display_player(x, y, img, 0x4500FF);
				my_mlx_pixel_put(img, (x * 45) + j, (y * 45) + i, 0x00FFFFFF);
			}
			x++;
		}
		y++;
	}
}

void ft_dislay(t_general *info, void *mlx, void *mlx_win)
{
	int i;
	int j;
	t_data *img;

	img = malloc(sizeof(t_data));
	i = 0;
	img->img = mlx_new_image(mlx, 45 * info->dimensions[0], 45 * info->dimensions[1]);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
								  &img->line_length, &img->endian);
	info->info_img = img;
	while (i < 45)
	{
		j = 0;
		while (j < 45)
		{
			display_pxl(info, img, j, i);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
}

void move_up(t_general *info, t_data *img)
{
	double pos_x;
	double pos_y;

	pos_x = info->info_player->pos_x + cos((info->alpha * PI) / 180) * 0.1;
	pos_y = info->info_player->pos_y + sin((info->alpha * PI) / 180) * 0.1;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		display_player(pos_x, pos_y, img, 0x00FF1FFF);
		display_player(info->info_player->pos_x, info->info_player->pos_y, img,
					   0x00FFFFFF);
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, img->img, 0, 0);
}

void move_down(t_general *info, t_data *img)
{
	double pos_x;
	double pos_y;

	pos_x = info->info_player->pos_x - cos((info->alpha * PI) / 180) * 0.1;
	pos_y = info->info_player->pos_y - sin((info->alpha * PI) / 180) * 0.1;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		display_player(pos_x, pos_y, img, 0x00FF1FFF);
		display_player(info->info_player->pos_x, info->info_player->pos_y, img,
					   0x00FFFFFF);
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, img->img, 0, 0);
}

void rotate_right(t_general *info)
{
	info->alpha += 1;
	if (info->alpha >= 360)
		info->alpha = 0;
}

void rotate_left(t_general *info)
{
	info->alpha -= 1;
	if (info->alpha < 0)
		info->alpha = 359;
}

bool break_wall(t_general *info, int x, int y)
{
	if (x < 0 || x >= info->dimensions[0])
		return false;
	if (y < 0 || y >= info->dimensions[1])
		return false;
	if (info->valid_map[y][x] == '1')
		return false;
	return true;
}

double horizontal(t_general *info, double alpha, t_coordinates *end)
{
	t_coordinates start;
	double x_steps;
	double y_steps;
	double beta = alpha;
	double atan = -1 / tan((( beta) * PI) / 180);
	start.i = info->info_player->pos_x * 45;
	start.j = info->info_player->pos_y * 45;
	if ( beta > 180)
	{
		end->j = ((int)(start.j / 45) * 45) - 0.0001;
		end->i = start.i + (start.j - end->j) * atan;
		y_steps = -45;
		x_steps = -y_steps * atan;
	}
	if ( beta < 180)
	{
		end->j = ((int)(start.j / 45) * 45) + 45;
		end->i = start.i + (start.j - end->j) * atan;
		y_steps = 45;
		x_steps = -y_steps * atan;
	}
	if ( beta == 0 ||  beta == 180)
		return INT_MAX;
	while (break_wall(info, (int)end->i / 45, (int)end->j / 45))
	{
		end->i += x_steps;
		end->j += y_steps;
	}
	if (end->j > INT_MAX || end->i > INT_MAX)
		return INT_MAX;
	if (end->j < INT_MIN || end->i < INT_MIN)
		return INT_MAX;
	double l = sqrt(pow(end->i - start.i,2) + pow(end->j - start.j,2));
	return l;
}

double vertecal(t_general *info, double alpha, t_coordinates *end)
{
	t_coordinates start;
	double x_steps;
	double y_steps;
	double beta = alpha;
	double atan = -tan(((beta) * PI) / 180);
	start.i = info->info_player->pos_x * 45;
	start.j = info->info_player->pos_y * 45;
	if (beta > 90 && beta < 270)
	{
		end->i = ((int)(start.i / 45) * 45) - 0.0001;
		end->j = start.j + (start.i - end->i) * atan;
		x_steps = -45;
		y_steps = -x_steps * atan;
	}
	if (beta < 90 || beta > 270)
	{
		end->i = ((int)(start.i / 45) * 45) + 45;
		end->j = start.j + (start.i - end->i) * atan;
		x_steps = 45;
		y_steps = -x_steps * atan;
	}
	if (beta == 90 || beta == 270)
		return INT_MAX;
	while (break_wall(info, (int)end->i / 45, (int)end->j / 45))
	{
		end->i += x_steps;
		end->j += y_steps;
	}
	if (end->j > INT_MAX || end->i > INT_MAX)
		return INT_MAX;
	if (end->j < INT_MIN || end->i < INT_MIN)
		return INT_MAX;
	double l = sqrt(pow(end->i - start.i,2) + pow(end->j - start.j,2));
	return l;
}

int draw_line(t_general *info, int color1, int color2)
{
	t_coordinates start;
	t_coordinates end;
	t_coordinates end1;
	start.i = info->info_player->pos_x * 45;
	start.j = info->info_player->pos_y * 45;
	double lv;
	double lh;
	int i;
	i = 0;
	double temp = 60 / ((double)info->dimensions[0] * 45);
	printf("2 thta: %f\n", info->bita_ray);
	while (i < info->dimensions[0] * 45)
	{ 	
		lv = vertecal(info, info->bita_ray,&end);
		lh = horizontal(info, info->bita_ray, &end1);
		if (lh > lv)
			sub_draw_line(info, &start, &end, color1);	
		else
			sub_draw_line(info, &start, &end1, color2);
		info->bita_ray += temp;
		if (info->bita_ray >= 360)
			info->bita_ray = 0;
		i++;
	}
	return 0;
}

int key_hook(int key, t_general *info)
{
	draw_line(info, 0xFFFFFF, 0xFFFFFF);
	info->bita_ray = info->alpha;
	int i = 0;
	double temp = 60 / ((double)info->dimensions[0] * 45);
	while(i < (info->dimensions[0] * 45) / 2)
	{
		if (info->bita_ray <= 0)
			info->bita_ray = 360;
		info->bita_ray -= temp;
		i++;
	}
	if (key == 65307)
		exit(0);
	else if (key == 65362 || key == 13)
		move_up(info, info->info_img);
	else if (key == 65364)
		move_down(info, info->info_img);
	else if (key == 65361)
		rotate_left(info);
	else if (key == 65363)
		rotate_right(info);
	draw_line(info, 0x00800080, 0x0000000);
	return (0);
}

void display_pixel(t_general info)
{
	info.alpha = 90;
	info.bita_ray = 90;
	printf("theta: %f \n", info.bita_ray);
	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, 45 * info.dimensions[0], 45 * info.dimensions[1], "cub3d");
	ft_dislay(&info, info.mlx, info.mlx_win);
	mlx_hook(info.mlx_win, 2, 3, key_hook, &info);
	mlx_loop(info.mlx);
}
