/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/12 04:51:40 by hlakhal-         ###   ########.fr       */
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
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 45 * info->dimensions[0], 45 * info->dimensions[1], "cub3d");
	// while (i < 45 * info->dimensions[0])
	// {
	// 	if (info->valid_map[])
	// 	{
	// 		/* code */
	// 	}

	// 	mlx_pixel_put(mlx,mlx_win,i,0, 0x00FF0000);
	// 	i++;
	// }
	mlx_loop(mlx);
}
