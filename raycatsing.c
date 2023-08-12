/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/12 22:19:47 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

// void dispaly(void *mlx, void *mlx_win, t_general *info)
// {
// 	mlx_pixel_put();
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void display_player(int x, int y, t_data img)
{
	int i;
	int j;

	i = 0;
	x *= 45;
	y *= 45;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(&img,x + j, y + i,0x4500FF);
			j++;
		}
		i++;
	}

}

void display_pixel(t_general *info)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int i;
	i = 0;
	int j;
	j = 0;
	int x;
	x = 0;
	int y;
	y = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 45 * info->dimensions[0], 45 * info->dimensions[1], "cub3d");
	img.img = mlx_new_image(mlx, 45 * info->dimensions[0], 45 * info->dimensions[1]);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	while (i < 45)
	{
		j = 0;
		while (j < 45)
		{
			y = 0;
			while(y < info->dimensions[1])
			{
				x = 0;
				while(x < info->dimensions[0])
				{
					//printf("%d | %d\n", (i * 45) + x ,(j * 45) + y);
					if (info->valid_map[y][x] == '1')
						my_mlx_pixel_put(&img, (x * 45) + j, (y * 45) + i, 0x00FF0000);
					if (info->valid_map[y][x] == '0')
						my_mlx_pixel_put(&img, (x * 45) + j, (y * 45) + i, 0x00FFFFFF);
					if (ft_strchr("NEWS", info->valid_map[y][x]))
					{
						display_player(x, y,img);
						my_mlx_pixel_put(&img, (x * 45) + j, (y * 45) + i, 0x00FFFFFF);
					}
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
