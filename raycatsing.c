/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/12 13:07:04 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

// void dispaly(void *mlx, void *mlx_win, t_general *info)
// {
// 	mlx_pixel_put();
// }

void display_pixel(t_general *info)
{
	void	*mlx;
	void	*mlx_win;
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
	// mlx_key_hook()
	// while (i < 45 * info->dimensions[0])
	// {
	// 	if (info->valid_map[])
	// 	{
	// 		/* code */
	// 	}

	// 	i++;
	// }
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
					printf("%d | %d\n", (i * 45) + x ,(j * 45) + y);
					if (info->valid_map[y][x] == '1')
						mlx_pixel_put(mlx,mlx_win,(x * 45) + j ,(y * 45) + i, 0xFFFF00);
					if (info->valid_map[y][x] == '0')
						mlx_pixel_put(mlx,mlx_win,(x * 45) + j ,(y * 45) + i, 0x00FFFF);
					if (ft_strchr("NEWS", info->valid_map[y][x]))
						mlx_pixel_put(mlx,mlx_win,(x * 45) + j ,(y * 45) + i, 0x00F00F);
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
