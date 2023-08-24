/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/24 13:02:12 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_general *info, int x, int y, int color)
{
	char	*dst;

	dst = info->info_img->addr + (y * info->info_img->line_length + x
			* (info->info_img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_get_pixel(t_data *texteur, int x, int y)
{
	char	*dst;

	dst = texteur->addr + (y * texteur->line_length + x
			* (texteur->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_help_1(t_general *info, double *i, double *d)
{
	if (info->wall_hight > (double)HEIGHT)
	{
		(*i) = fabs((info->wall_hight / 2) - ((double)HEIGHT / 2));
		(*d) = info->wall_hight;
	}
	else
	{
		(*i) = 0;
		(*d) = HEIGHT;
	}
}

void	draw_help(t_general *info, t_data *texteur, int steps, double img_x)
{
	t_drawing	draw;

	draw.k = 0;
	draw.i = 0;
	draw.x_crement = (float)(int)(info->end->i - info->start->i) / (float)steps;
	draw.y_crement = (float)(int)(info->end->j - info->start->j) / (float)steps;
	draw.x = info->start->i;
	draw.y = info->start->j;
	draw_help_1(info, &draw.i, &draw.d);
	while (draw.i < draw.d)
	{
		my_mlx_pixel_put(info, (int)draw.x, (int)draw.y,
				my_mlx_get_pixel(texteur, (int)img_x, (int)draw.k));
		draw.k = draw.i / info->wall_hight * texteur->height;
		draw.x += draw.x_crement;
		draw.y += draw.y_crement;
		if (draw.x > WIDTH || draw.y > HEIGHT || draw.k > texteur->height)
			break ;
		draw.i++;
	}
}

void	sub_draw_line(t_general *info, double endi, t_data *texteur)
{
	int		steps;
	double	img_x;

	if (abs((int)(info->end->i - info->start->i)) > abs((int)(info->end->j
				- info->start->j)))
		steps = abs((int)(info->end->i - info->start->i));
	else
		steps = abs((int)(info->end->j - info->start->j));
	img_x = ((int)texteur->width * (endi / 45 - floor(endi / 45)));
	draw_help(info, texteur, steps, img_x);
}

int	get_color(t_general *info, char c)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (info->info_rgb[i].type_color[0] == c)
			return (rgbToHex(info->info_rgb[i]._R, info->info_rgb[i]._G,
					info->info_rgb[i]._B));
		i++;
	}
	return (0);
}

void	display_floor(t_general *info, t_data *img, int j, int i)
{
	int	x;
	int	y;

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

void	display_sky(t_general *info, t_data *img, int j, int i)
{
	int	x;
	int	y;

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
void	ft_dislay(t_general *info, void *mlx, void *mlx_win)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	display_floor(info, info->info_img->img, j, i);
	display_sky(info, info->info_img->img, j, i);
	calcule_bite_ray(info);
	draw_line(info);
	mlx_put_image_to_window(mlx, mlx_win, info->info_img->img, 0, 0);
}

void	move_up(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x + cos((info->alpha * PI) / 180) * SPEED;
	pos_y = info->info_player->pos_y + sin((info->alpha * PI) / 180) * SPEED;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
}

void	move_down(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x - cos((info->alpha * PI) / 180) * SPEED;
	pos_y = info->info_player->pos_y - sin((info->alpha * PI) / 180) * SPEED;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
}

void	move_left(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x + cos(((info->alpha - 270) * PI) / 180)
		* (SPEED - 0.05);
	pos_y = info->info_player->pos_y + sin(((info->alpha - 270) * PI) / 180)
		* (SPEED - 0.05);
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
}

void	move_right(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x - cos(((info->alpha + 90) * PI) / 180)
		* (SPEED - 0.05);
	pos_y = info->info_player->pos_y - sin(((info->alpha + 90) * PI) / 180)
		* (SPEED - 0.05);
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
}

void	rotate_right(t_general *info)
{
	info->alpha += SPEEDALPHA;
	if (info->alpha >= 360)
		info->alpha = 0;
}

void	rotate_left(t_general *info)
{
	info->alpha -= SPEEDALPHA;
	if (info->alpha < 0)
		info->alpha = 359;
}

bool	break_wall(t_general *info, int x, int y)
{
	if (x < 0 || x >= info->dimensions[0])
		return (false);
	if (y < 0 || y >= info->dimensions[1])
		return (false);
	if (info->valid_map[y][x] == '1' || info->valid_map[y][x] == 32)
		return (false);
	return (true);
}

void	step_rays(t_general *info, double *x_steps, double *y_steps,
		double beta)
{
	double	atan;

	atan = -1 / tan(((beta)*PI) / 180);
	info->start->i = info->info_player->pos_x * 45;
	info->start->j = info->info_player->pos_y * 45;
	if (beta > 180)
	{
		info->end->j = ((int)(info->start->j / 45) * 45) - 0.0001;
		info->end->i = info->start->i + (info->start->j - info->end->j) * atan;
		(*y_steps) = -45;
		(*x_steps) = -(*y_steps) * atan;
	}
	if (beta < 180)
	{
		info->end->j = ((int)(info->start->j / 45) * 45) + 45;
		info->end->i = info->start->i + (info->start->j - info->end->j) * atan;
		(*y_steps) = 45;
		(*x_steps) = -(*y_steps) * atan;
	}
}

void	set_len(t_general *info, t_casted_ray *h)
{
	double	l;

	l = sqrt(pow(info->end->i - info->start->i, 2) + pow(info->end->j
				- info->start->j, 2));
	h->lenght = l;
	h->end.i = info->end->i;
	h->end.j = info->end->j;
}

t_casted_ray	*horizontal(t_general *info, double beta)
{
	t_casted_ray	*h;
	double			x_steps;
	double			y_steps;

	h = malloc(sizeof(t_casted_ray));
	step_rays(info, &x_steps, &y_steps, beta);
	if (beta == 0 || beta == 180)
	{
		h->lenght = INT_MAX;
		h->end.i = info->end->i;
		h->end.j = info->end->j;
		return (h);
	}
	while (break_wall(info, (int)info->end->i / 45, (int)info->end->j / 45))
	{
		info->end->i += x_steps;
		info->end->j += y_steps;
	}
	if (info->end->j > INT_MAX || info->end->i > INT_MAX
		|| info->end->j < INT_MIN || info->end->i < INT_MIN)
	{
		h->lenght = INT_MAX;
		return (h);
	}
	return (set_len(info, h), h);
}

void	step_rays_v(t_general *info, double *x_steps, double *y_steps,
		double beta)
{
	double	atan;

	atan = -tan(((beta)*PI) / 180);
	info->start->i = info->info_player->pos_x * 45;
	info->start->j = info->info_player->pos_y * 45;
	if (beta > 90 && beta < 270)
	{
		info->end->i = ((int)(info->start->i / 45) * 45) - 0.0001;
		info->end->j = info->start->j + (info->start->i - info->end->i) * atan;
		(*x_steps) = -45;
		(*y_steps) = -(*x_steps) * atan;
	}
	if (beta < 90 || beta > 270)
	{
		info->end->i = ((int)(info->start->i / 45) * 45) + 45;
		info->end->j = info->start->j + (info->start->i - info->end->i) * atan;
		(*x_steps) = 45;
		(*y_steps) = -(*x_steps) * atan;
	}
}

t_casted_ray	*vertecal(t_general *info, double beta)
{
	t_casted_ray	*v;
	double			x_steps;
	double			y_steps;

	v = malloc(sizeof(t_casted_ray));
	step_rays_v(info, &x_steps, &y_steps, beta);
	if (beta == 90 || beta == 270)
	{
		v->lenght = INT_MAX;
		v->end.i = info->end->i;
		v->end.j = info->end->j;
		return (v);
	}
	while (break_wall(info, (int)info->end->i / 45, (int)info->end->j / 45))
	{
		info->end->i += x_steps;
		info->end->j += y_steps;
	}
	if (info->end->j > INT_MAX || info->end->i > INT_MAX
		|| info->end->j < INT_MIN || info->end->i < INT_MIN)
	{
		v->lenght = INT_MAX;
		return (v);
	}
	return (set_len(info, v), v);
}

double	calcule_projection(t_general *info)
{
	int	half_width;

	(void)info;
	half_width = WIDTH / 2;
	return (half_width / tan((30 * PI) / 180));
}
t_data	*get_side_texteur(t_general *info, char *str)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(str, info->info_texteur[i].direction, 2))
			return (info->info_texteur[i].texteur);
		i++;
	}
	return (info->info_texteur[0].texteur);
}

void	calcule_of_wall(t_general *info, int i, t_coordinates *start)
{
	double	projec;

	info->v = vertecal(info, info->bita_ray);
	info->h = horizontal(info, info->bita_ray);
	projec = calcule_projection(info);
	start->i = i;
	info->end->i = i;
	info->wall_hight = ((projec * 45) / (fmin(info->v->lenght, info->h->lenght)
				* cos(((info->bita_ray - info->alpha) * PI) / 180)));
	start->j = (HEIGHT / 2) - info->wall_hight / 2;
	start->j *= start->j > 0;
	info->end->j = (HEIGHT / 2) + info->wall_hight / 2;
	if (info->end->j > HEIGHT)
		info->end->j = HEIGHT;
}

void	draw_texteur(t_general *info)
{
	if (info->h->lenght > info->v->lenght)
	{
		if (cos((info->bita_ray * PI) / 180) > 0)
			sub_draw_line(info, info->v->end.j, get_side_texteur(info, "EA"));
		else if (cos((info->bita_ray * PI) / 180) < 0)
			sub_draw_line(info, info->v->end.j, get_side_texteur(info, "WE"));
	}
	else
	{
		if (sin(((info->bita_ray * PI) / 180)) > 0)
			sub_draw_line(info, info->h->end.i, get_side_texteur(info, "SO"));
		else if (sin(((info->bita_ray * PI) / 180)) < 0)
			sub_draw_line(info, info->h->end.i, get_side_texteur(info, "NO"));
	}
}

int	draw_line(t_general *info)
{
	int		i;
	double	temp;

	info->end = malloc(sizeof(t_coordinates));
	info->start = malloc(sizeof(t_coordinates));
	i = 0;
	temp = 60 / ((double)WIDTH);
	while (i < WIDTH)
	{
		calcule_of_wall(info, i, info->start);
		draw_texteur(info);
		info->bita_ray += temp;
		if (info->bita_ray >= 360)
			info->bita_ray = 0;
		free(info->h);
		free(info->v);
		i++;
	}
	free(info->end);
	free(info->start);
	return (0);
}

void	calcule_bite_ray(t_general *info)
{
	int		i;
	double	temp;

	info->bita_ray = info->alpha;
	i = 0;
	temp = 60 / ((double)WIDTH);
	while (i < (WIDTH) / 2)
	{
		if (info->bita_ray <= 0)
			info->bita_ray = 360;
		info->bita_ray -= temp;
		i++;
	}
}

int	key_hook(int key, t_general *info)
{
	calcule_bite_ray(info);
	ft_dislay(info, info->mlx, info->mlx_win);
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
	ft_mini_map(info, info->mlx, info->mlx_win);
	return (0);
}

double	get_alpha_player(t_general info)
{
	if (info.info_player->direction == 'N')
		return (270);
	if (info.info_player->direction == 'E')
		return (0);
	if (info.info_player->direction == 'S')
		return (90);
	if (info.info_player->direction == 'W')
		return (180);
	return (0);
}
void	get_texters(t_general *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		info->info_texteur[i].texteur = malloc(sizeof(t_data));
		info->info_texteur[i].texteur->img = mlx_xpm_file_to_image(info->mlx,
				info->info_texteur[i].path,
				&info->info_texteur[i].texteur->width,
				&info->info_texteur[i].texteur->height);
		if (!info->info_texteur[i].texteur->img)
		{
			printf("image not found!");
			exit(2);
		}
		info->info_texteur[i].texteur->addr = mlx_get_data_addr(
				info->info_texteur[i].texteur->img,
				&info->info_texteur[i].texteur->bits_per_pixel,
				&info->info_texteur[i].texteur->line_length,
				&info->info_texteur[i].texteur->endian);
		i++;
	}
}

int	mouse_hook(int keycode, t_general *info)
{
	(void)info;
	int a,b;
	(void)keycode;
	printf("Hello from key_hook! %d\n", mlx_mouse_get_pos(info->mlx, info->mlx_win, &a, &b));
	return (0);
}
int	close_win(int keycode, t_general *info)
{
	(void)info;
	(void)keycode;
	printf("closed by ESC! \n");
	exit(0);
}

void	display_pixel(t_general info)
{
	info.alpha = get_alpha_player(info);
	info.bita_ray = info.alpha;
	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "cub3d");
	info.info_img = malloc(sizeof(t_data));
	info.info_img->img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.info_img->addr = mlx_get_data_addr(info.info_img->img,
			&info.info_img->bits_per_pixel, &info.info_img->line_length,
			&info.info_img->endian);
	info.mini_map = malloc(sizeof(t_data));
	info.mini_map->img = mlx_new_image(info.mlx, 300, 100);
	info.mini_map->addr = mlx_get_data_addr(info.mini_map->img,
			&info.mini_map->bits_per_pixel, &info.mini_map->line_length,
			&info.mini_map->endian);
	get_texters(&info);
	ft_dislay(&info, info.mlx, info.mlx_win);	
	mlx_hook(info.mlx_win, 2, 3, key_hook, &info);
	// mlx_hook(info.mlx_win, 6, 3, mouse_hook, &info);
	mlx_mouse_hook(info.mlx_win, mouse_hook, &info);
	mlx_hook(info.mlx_win, 17, 0, close_win, &info);
	mlx_loop(info.mlx);
}
