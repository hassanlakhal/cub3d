/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/30 15:58:41 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	display_pixel(t_general info)
{
	info.alpha = get_alpha_player(info);
	info.bita_ray = info.alpha;
	info.mlx = mlx_init();
	get_texters(&info);
	info.mlx_win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "cub3d");
	info.info_img = malloc(sizeof(t_data));
	if (!info.info_img)
		return ;
	info.info_img->img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.info_img->addr = mlx_get_data_addr(info.info_img->img,
			&info.info_img->bits_per_pixel,
			&info.info_img->line_length,
			&info.info_img->endian);
	ft_dislay(&info, info.mlx, info.mlx_win);
	mlx_hook(info.mlx_win, 2, 3, key_hook, &info);
	mlx_hook(info.mlx_win, 17, 0, close_win, &info);
	mlx_loop(info.mlx);
}
