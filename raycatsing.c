/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/13 22:33:29 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void dispaly(void *mlx, void *mlx_win, t_general *info)
// {
// 	mlx_pixel_put();
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	//printf("a|h%d    y:%d|\n",data->height,y);
		//printf("b|h:%d   y:%d|\n",data->height,y);
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
}

void	display_player(double x, double y, t_data *img, int color)
{
	int	i;
	int	j;

	i = 0;
	x *= 45;
	y *= 45;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	display_pxl(t_general *info, t_data *img, int j, int i)
{
	int	y;
	int	x;

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

void	ft_dislay(t_general *info, void *mlx, void *mlx_win)
{
	int		i;
	int		j;
	t_data	*img;

	img = malloc(sizeof(t_data));
	i = 0;
	// img->width = 45 * info->dimensions[0];
	// img->height = 45 * info->dimensions[1];
	img->img = mlx_new_image(mlx, 45 * info->dimensions[0], 45
			* info->dimensions[1]);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
			&img->endian);
	info->info_img = img;
	printf("add %p\n", img->img);
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

void	move_up(t_general *info, t_data *img)
{

	double pos_x;
	double pos_y;

	pos_x = info->info_player->pos_x + cos((info->alpha*PI)/180) * 0.1;
	pos_y = info->info_player->pos_y + sin((info->alpha*PI)/180) * 0.1;
	
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		display_player(pos_x, pos_y, img, 0x00FF1FFF);
		display_player(info->info_player->pos_x, info->info_player->pos_y, img, 0x00FFFFFF);
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, img->img, 0, 0);
}

void	move_down(t_general *info, t_data *img)
{

	double pos_x;
	double pos_y;

	pos_x = info->info_player->pos_x - cos((info->alpha*PI)/180) * 0.1;
	pos_y = info->info_player->pos_y - sin((info->alpha*PI)/180) * 0.1;
	
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		display_player(pos_x, pos_y, img, 0x00FF1FFF);
		display_player(info->info_player->pos_x, info->info_player->pos_y, img, 0x00FFFFFF);
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, img->img, 0, 0);
}

void	rotate_right(t_general *info)
{
	info->alpha += 10;
}
void	rotate_left(t_general *info)
{
	info->alpha -= 10;
}

int	draw_rays(t_general *info)
{
	int i;

	double pos_x;
	double pos_y;
	double old_pos_x;
	double old_pos_y;

	pos_x = info->info_player->pos_x * 45 + cos((info->alpha * PI) / 180) * 0.1;
	pos_y = info->info_player->pos_y * 45 + sin((info->alpha * PI) / 180) * 0.1;
	printf("%f\t%f\t%f\n", info->alpha,pos_x, pos_y);
	old_pos_x = pos_x;
	old_pos_y = pos_y;
	i = 0;
	while(i < 700)
	{
		my_mlx_pixel_put(info->info_img, pos_x, pos_y, 0x001F11FF);
		my_mlx_pixel_put(info->info_img, old_pos_x, old_pos_y, 0x00000000);
		old_pos_x = pos_x;
		old_pos_y = pos_y;
		pos_x += 0.1;
		pos_y += 0.1;
		i++;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->info_img->img, 0, 0);
	return 0;
}

int	key_hook(int key, t_general *info)
{
	if (key == 53)
		exit(0);
	else if (key == 126 || key == 13)
		move_up(info, info->info_img);
	else if (key == 125 )
		move_down(info, info->info_img);
	else if (key == 124)
		rotate_right(info);
	else if (key == 123)
		rotate_left(info);
	return (0);
}

void	display_pixel(t_general info)
{
	// void	*mlx;
	// void	*mlx_win;
	info.alpha = 0;
	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, 45 * info.dimensions[0], 45
			* info.dimensions[1], "cub3d");
	ft_dislay(&info, info.mlx, info.mlx_win);
	mlx_key_hook(info.mlx_win, key_hook, &info);
	mlx_loop_hook(info.mlx, draw_rays, &info);
	mlx_loop(info.mlx);
}
