/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/21 12:04:18 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_mlx_pixel_put(t_general *info, int x, int y, int color)
{
	char *dst;
	dst = info->info_img->addr + (y * info->info_img->line_length + x * (info->info_img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int my_mlx_get_pixel(t_general *info, int x, int y)
{
	char *dst;
	dst = info->texteur->addr + (y * info->texteur->line_length + x * (info->texteur->bits_per_pixel / 8));
	return *(unsigned int *)dst;
}

void sub_draw_line(t_general *info, t_coordinates *start, t_coordinates *end,double endi,double wall_hight)
{

	int dx = (end->i - start->i);
	int dy = (end->j - start->j);
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float xIncrement = (float)dx / (float)steps;
	float yIncrement = (float)dy / (float)steps;
	float x = start->i;
	float y = start->j;
	double obj_x = endi / 45 - floor(endi / 45);
	double img_x = ((int)info->texteur->width  * obj_x);
	int k = 0;
	for (int i = 0; i < wall_hight; i++)
	{
		my_mlx_pixel_put(info, (int)x, (int)y, my_mlx_get_pixel(info, (int)img_x, (int)k));
		k = i / wall_hight * info->texteur->height;
		x += xIncrement;
		y += yIncrement;
		if (i >= steps || k >= info->texteur->height)
			break;
	}
}

// void display_player(double x, double y, t_data *img, int color)
// {
// 	x *= 45;
// 	y *= 45;

// 	my_mlx_pixel_put(img, (int)x, (int)y, color);
// }

void display_pxl(t_general *info, t_data *img, int j, int i)
{
	int y;
	int x;

	y = 0;
	(void)img;
	while (y < info->dimensions[1] / 2)
	{
		x = 0;
		while (x < info->dimensions[0])
		{
			// if (info->valid_map[y][x] == '1')
			my_mlx_pixel_put(info, (x * 45) + j, (y * 45) + i, 0x00FF0000);
			// if (info->valid_map[y][x] == '0')
			// 	my_mlx_pixel_put(img, (x * 45) + j, (y * 45) + i, 0x00FFFFFF);
			// if (ft_strchr("NEWS", info->valid_map[y][x]))
			// {
			// 	display_player(x, y, img, 0x4500FF);
			// 	my_mlx_pixel_put(img, (x * 45) + j, (y * 45) + i, 0x00FFFFFF);
			// }
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->info_img->img, 0, 0);
}

int get_color(t_general *info, char c)
{
	int i;

	i = 0;
	while(i < 2)
	{
		if (info->info_rgb[i].type_color[0] == c)
			return rgbToHex(info->info_rgb[i]._R, info->info_rgb[i]._G, info->info_rgb[i]._B);
		i++;
	}
	return 0;
}

void display_floor(t_general *info, t_data *img, int j, int i)
{

	int x;
	int y;

	x = 0;
	y = 0;
	(void)i;
	(void)j;
	(void)img;
	while (x < WIDTH)
	{
		y = (int)HEIGHT / 2;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(info, x, y, get_color(info, 'F'));
			y++;
		}
		x++;
	}
}

void display_sky(t_general *info, t_data *img, int j, int i)
{
	int x;
	int y;

	x = 0;
	y = 0;
	(void)img;
	(void)i;
	(void)j;

	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			my_mlx_pixel_put(info, x, y, get_color(info, 'C'));
			y++;
		}
		x++;
	}
}
void ft_dislay(t_general *info, void *mlx, void *mlx_win)
{
	int i;
	int j = 0;
	i = 0;
	// while (i < 45)
	// {
	// 	j = 0;
	// 	while (j < 45)
	// 	{
			display_floor(info, info->info_img->img, j, i);
			display_sky(info, info->info_img->img, j, i);
	// 		j++;
	// 	}
	// 	i++;
	// }
	mlx_put_image_to_window(mlx, mlx_win, info->info_img->img, 0, 0);
}

void move_up(t_general *info, t_data *img)
{
	double pos_x;
	double pos_y;
	(void)img;

	pos_x = info->info_player->pos_x + cos((info->alpha * PI) / 180) * SPEED;
	pos_y = info->info_player->pos_y + sin((info->alpha * PI) / 180) * SPEED;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
}

void move_down(t_general *info, t_data *img)
{
	double pos_x;
	double pos_y;
	(void)img;

	pos_x = info->info_player->pos_x - cos((info->alpha * PI) / 180) * SPEED;
	pos_y = info->info_player->pos_y - sin((info->alpha * PI) / 180) * SPEED;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
}

void move_left(t_general *info, t_data *img)
{
	double pos_x;
	double pos_y;
	(void)img;

	pos_x = info->info_player->pos_x + cos(((info->alpha - 270) * PI) / 180) * (SPEED - 0.05);
	pos_y = info->info_player->pos_y + sin(((info->alpha - 270) * PI) / 180) * (SPEED - 0.05);
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
}

void move_right(t_general *info, t_data *img)
{
	double pos_x;
	double pos_y;
	(void)img;

	pos_x = info->info_player->pos_x - cos(((info->alpha + 90) * PI) / 180) * (SPEED - 0.05);
	pos_y = info->info_player->pos_y - sin(((info->alpha + 90) * PI) / 180) * (SPEED - 0.05);
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
}

void rotate_right(t_general *info)
{
	info->alpha += SPEEDALPHA;
	if (info->alpha >= 360)
		info->alpha = 0;
}

void rotate_left(t_general *info)
{
	info->alpha -= SPEEDALPHA;
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

t_casted_ray  horizontal(t_general *info, double alpha, t_coordinates *end)
{
	t_coordinates start;
	t_casted_ray h;
	start.i = info->info_player->pos_x * 45;
	start.j = info->info_player->pos_y * 45;
	double x_steps;
	double y_steps;
	double beta = alpha;
	double atan = -1 / tan(((beta)*PI) / 180);
	start.i = info->info_player->pos_x * 45;
	start.j = info->info_player->pos_y * 45;
	if (beta > 180)
	{
		end->j = ((int)(start.j / 45) * 45) - 0.0001;
		end->i = start.i + (start.j - end->j) * atan;
		y_steps = -45;
		x_steps = -y_steps * atan;
	}
	if (beta < 180)
	{
		end->j = ((int)(start.j / 45) * 45) + 45;
		end->i = start.i + (start.j - end->j) * atan;
		y_steps = 45;
		x_steps = -y_steps * atan;
	}
	if (beta == 0 || beta == 180)
	{
		h.lenght = INT_MAX;
		return h;
	}
	while (break_wall(info, (int)end->i / 45, (int)end->j / 45))
	{
		end->i += x_steps;
		end->j += y_steps;
	}
	if (end->j > INT_MAX || end->i > INT_MAX)
	{
		h.lenght = INT_MAX;
		h.end.i = end->i;
	h.end.j = end->j;
		return h;
	}
	if (end->j < INT_MIN || end->i < INT_MIN)
	{
		h.lenght = INT_MAX;
		h.end.i = end->i;
	h.end.j = end->j;
		return h;
	}
	double l = sqrt(pow(end->i - start.i, 2) + pow(end->j - start.j, 2));
	
	h.lenght = l;
	h.end.i = end->i;
	h.end.j = end->j;
	
	return h;
}

t_casted_ray vertecal(t_general *info, double alpha, t_coordinates *end)
{
	t_coordinates start;
	t_casted_ray v;
	start.i = info->info_player->pos_x * 45;
	start.j = info->info_player->pos_y * 45;
	double x_steps;
	double y_steps;
	double beta = alpha;
	double atan = -tan(((beta)*PI) / 180);
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
	{
		v.lenght = INT_MAX;
		v.end.i = end->i;
	v.end.j = end->j;
		return v;
	}
	while (break_wall(info, (int)end->i / 45, (int)end->j / 45))
	{
		end->i += x_steps;
		end->j += y_steps;
	}
	if (end->j > INT_MAX || end->i > INT_MAX)
	{
		v.lenght = INT_MAX;
		v.end.i = end->i;
	v.end.j = end->j;
		return v;
	}
	if (end->j < INT_MIN || end->i < INT_MIN)
	{
		v.lenght = INT_MAX;
		v.end.i = end->i;
	v.end.j = end->j;
		return v;
	}
	double l = sqrt(pow(end->i - start.i, 2) + pow(end->j - start.j, 2));
	v.lenght = l;
	v.end.i = end->i;
	v.end.j = end->j;
	return v;
}

double calcule_projection(t_general *info)
{
	(void)info;
	int half_width = WIDTH / 2;
	return (half_width / tan((30 * PI) / 180));
}

int draw_line(t_general *info, int color1, int color2)
{
	t_coordinates start;
	t_coordinates end;
	t_coordinates end1;

	t_casted_ray v;
	t_casted_ray h;

	(void)color1;
	(void)color2;
	double projec;
	double wall_hight;
	int i;
	i = 0;
	double temp = 60 / ((double)WIDTH);
	while (i < WIDTH)
	{
		v = vertecal(info, info->bita_ray, &end);
		h = horizontal(info, info->bita_ray, &end1);
		projec = calcule_projection(info);
		start.i = i;
		end.i = i;
		if (h.lenght > v.lenght)
		{
			wall_hight = ((projec * 45) / (v.lenght * cos(((info->bita_ray - info->alpha) * PI) / 180)));
			start.j = (HEIGHT / 2) - wall_hight / 2;
			start.j *= start.j > 0;
			end.j = (HEIGHT / 2) + wall_hight / 2;
			if (end.j > HEIGHT)
				end.j = HEIGHT;
			if (cos((info->bita_ray * PI)/180) > 0)
			{
				sub_draw_line(info, &start, &end, v.end.j ,wall_hight);
			}
			else if(cos((info->bita_ray * PI)/180) < 0)
				sub_draw_line(info, &start, &end, v.end.j ,wall_hight);

		}
		else
		{
			wall_hight = ((projec * 45) / (h.lenght * cos(((info->bita_ray - info->alpha) * PI) / 180)));
			start.j = (HEIGHT/ 2) - wall_hight / 2;
			start.j *= start.j > 0;
			end.j = (HEIGHT/ 2) + wall_hight / 2;
			if (end.j > HEIGHT)
				end.j = HEIGHT;
			if (sin(((info->bita_ray * PI)/180)) > 0)
				sub_draw_line(info, &start, &end, h.end.i ,wall_hight);
			else if (sin(((info->bita_ray * PI)/180)) < 0)
				sub_draw_line(info, &start, &end, h.end.i ,wall_hight);
		}
		info->bita_ray += temp;
		if (info->bita_ray >= 360)
			info->bita_ray = 0;
		i++;
	}
	return 0;
}

void calcule_bite_ray(t_general *info)
{
	info->bita_ray = info->alpha;
	int i = 0;
	double temp = 60 / ((double)WIDTH );
	while (i < (WIDTH) / 2)
	{
		if (info->bita_ray <= 0)
			info->bita_ray = 360;
		info->bita_ray -= temp;
		i++;
	}
}

int key_hook(int key, t_general *info)
{
	ft_dislay(info, info->mlx, info->mlx_win);
	calcule_bite_ray(info);
	if (key == 65307)
		exit(0);
	else if (key == 65362 || key == 119)
		move_up(info, info->info_img);
	else if (key == 65364 || key == 115)
		move_down(info, info->info_img);
	else if (key == 97)
		move_right(info, info->info_img);
	else if (key == 100)
		move_left(info, info->info_img);
	else if (key == 65361)
		rotate_left(info);
	else if (key == 65363)
		rotate_right(info);
	
	draw_line(info, 0x999900, 0x0880000);
	return (0);
}
double get_alpha_player(t_general info)
{
	if (info.info_player->direction == 'N')
		return 270;
	if (info.info_player->direction == 'E')
		return 0;
	if (info.info_player->direction == 'S')
		return 90;
	if (info.info_player->direction == 'W')
		return 180;
	return 0;
}
void display_pixel(t_general info)
{

	info.alpha = get_alpha_player(info);
	info.bita_ray = info.alpha;
	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "cub3d");
	
	info.info_img = malloc(sizeof(t_data));
	info.info_img->img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.info_img->addr = mlx_get_data_addr(info.info_img->img, &info.info_img->bits_per_pixel, &info.info_img->line_length, &info.info_img->endian);
	
	info.texteur = malloc(sizeof(t_data));
	info.texteur->img = mlx_xpm_file_to_image(info.mlx, "texture/wall.xpm", &info.texteur->width, &info.texteur->height);
	info.texteur->addr = mlx_get_data_addr(info.texteur->img, &info.texteur->bits_per_pixel, &info.texteur->line_length, &info.texteur->endian);
	 
	ft_dislay(&info, info.mlx, info.mlx_win);
	mlx_hook(info.mlx_win, 2, 3, key_hook, &info);
	mlx_loop(info.mlx);
}
