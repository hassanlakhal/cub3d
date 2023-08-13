/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/13 16:57:20 by rlarabi          ###   ########.fr       */
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
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
}

void	display_player(int x, int y, t_data *img, int color)
{
	int	i;
	int	j;

	i = 0;
	x *= 45;
	y *= 45;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
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
	int	new_x;
	int	new_y;

	new_y = info->info_player->pos_y - 1;
	new_x = info->info_player->pos_x;
	// img->height = 45 * new_y;
	// img->width = 45 * new_x;
	//mlx_pixel_put(info->mlx, info->mlx_win, new_x * 45, new_y * 45, 0x000000);
	if (info->valid_map[(int)new_y][(int)new_x] != '1')
	{
		printf("add %p\n", img->img);
		printf("* %d %d\n",new_x, new_y);
		display_player(info->info_player->pos_x, info->info_player->pos_y, img,
				0x00FFFFFF);
		display_player(new_x, new_y, img, 0x4500FFF);
		info->info_player->pos_y = new_y;
		info->info_player->pos_x = new_x;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, img->img, 0, 0);
}

int	key_hook(int key, t_general *info)
{
	if (key == 53)
		exit(0);
	if (key == 126 || key == 13)
		move_up(info, info->info_img);
	return (0);
}

void	display_pixel(t_general info)
{
	// void	*mlx;
	// void	*mlx_win;

	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, 45 * info.dimensions[0], 45
			* info.dimensions[1], "cub3d");
	ft_dislay(&info, info.mlx, info.mlx_win);
	mlx_key_hook(info.mlx_win, key_hook, &info);
	mlx_loop(info.mlx);
}
