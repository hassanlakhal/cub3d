/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/12 20:13:15 by hlakhal-         ###   ########.fr       */
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
	printf("info->dimensions[1] %d\t info->dimensions[0] %d\n", info->dimensions[1], info->dimensions[0]);
	//exit(0);
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
					{
						my_mlx_pixel_put(&img, (x * 45) + j, (y * 45) + i, 0x00FF0000);
						mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
					}
					// if (info->valid_map[y][x] == '0')
					// 	mlx_pixel_put(mlx,mlx_win,(x * 45) + j ,(y * 45) + i, 0x00000F);
					// if (ft_strchr("NEWS", info->valid_map[y][x]))
					// {
					// 	printf("|x:%d|\t|y:%d|\n",info->info_player->pos_x,info->info_player->pos_y);
					// 	mlx_pixel_put(mlx,mlx_win, (info->info_player->pos_x * 20) + 1 ,(info->info_player->pos_y * 20) + 1, 0x00F00F);
					// }
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}

	printf("|%s|\n",info->valid_map[0]);
	printf("|%s|\n",info->valid_map[1]);
	printf("|%s|\n",info->valid_map[2]);
	printf("|%s|\n",info->valid_map[3]);
	printf("|%s|\n",info->valid_map[4]);
	printf("|%s|\n",info->valid_map[5]);
	mlx_loop(mlx);
}
