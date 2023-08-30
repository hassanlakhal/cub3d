/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:04:08 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/30 15:58:56 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_draw_floor_sky(t_general *info, t_drawing draw)
{
	int	p;

	p = 0;
	while (p < info->start->j)
	{
		my_mlx_pixel_put(info, (int)draw.x, p, get_color(info, 'C'));
		p++;
	}
	p = info->end->j;
	while (p < HEIGHT)
	{
		my_mlx_pixel_put(info, (int)draw.x, p, get_color(info, 'F'));
		p++;
	}
}

void	ft_dislay(t_general *info, void *mlx, void *mlx_win)
{
	(void)mlx;
	(void)mlx_win;
	mlx_destroy_image(info->mlx, info->info_img->img);
	info->info_img->img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->info_img->addr = mlx_get_data_addr(info->info_img->img,
			&info->info_img->bits_per_pixel,
			&info->info_img->line_length,
			&info->info_img->endian);
	calcule_bite_ray(info);
	draw_line(info);
	mlx_put_image_to_window(mlx, mlx_win, info->info_img->img, 0, 0);
}
