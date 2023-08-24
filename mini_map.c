/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:23:08 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/24 12:34:00 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_display_player(t_general *info, int x, int y)
{
	double	i;
	double	j;

	i = 0;
	while (i < 2.5)
	{
		j = 0;
		while (j < 2.5)
		{
			my_mlx_pixel_put(info, x + j, y + i, 0xFF3333FF);
			j++;
		}
		i++;
	}
}

void	ft_display_mini(t_general *info, int i, int j)
{
	double	x;
	double	y;
	int		original_map_x;
	int		original_map_y;

	y = -1;
	while (++y < 100)
	{
		x = 0;
		while (x < 200)
		{
			original_map_x = (int)(x * (double)info->dimensions[0] / 200.00);
			original_map_y = (int)(y * (double)info->dimensions[1] / 100.00);
			if (original_map_x < info->dimensions[0]
				&& original_map_y < info->dimensions[1])
			{
				if (info->valid_map[original_map_y][original_map_x] == '1'
					|| info->valid_map[original_map_y][original_map_x] == 32)
					my_mlx_pixel_put(info, x + j, y + i, 0x455545);
				else
					my_mlx_pixel_put(info, x + j, y + i, 0x195545);
			}
			x++;
		}
	}
}

void	ft_mini_map(t_general *info, void *mlx, void *mlx_win)
{
	int i;
	int j;
	(void)mlx;
	(void)mlx_win;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			ft_display_mini(info, i, j);
			j++;
		}
		i++;
	}
	ft_display_player(info, (info->info_player->pos_x * (200.00
					/ info->dimensions[0])), (info->info_player->pos_y * (100.00
					/ info->dimensions[1])));
}
