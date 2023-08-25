/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:04:08 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/25 13:04:29 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	ft_mini_map(info, info->mlx, info->mlx_win);
	mlx_put_image_to_window(mlx, mlx_win, info->info_img->img, 0, 0);
}