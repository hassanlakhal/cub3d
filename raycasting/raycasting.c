/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/25 13:22:10 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



int	key_hook(int key, t_general *info)
{
	calcule_bite_ray(info);
	ft_dislay(info, info->mlx, info->mlx_win);
	if (key == 65307)
		exit(0);
	else if (key == 65362 || key == 119)
		move_up(info, info->info_img);
	else if (key == 65364 || key == 115)
		move_down(info, info->info_img);
	else if (key == 97)
		move_right(info, info->info_img);
	else if (key == 100)
		move_left(info, info->info_img);
	else if (key == 65361)
		rotate_left(info);
	else if (key == 65363)
		rotate_right(info);
	ft_mini_map(info, info->mlx, info->mlx_win);
	return (0);
}


// int	mouse_hook(int key_code, t_fractal *fractal)
int	mouse_hook_1(int x, int y, t_general *info)
{
	(void)y;
	calcule_bite_ray(info);
	ft_dislay(info, info->mlx, info->mlx_win);
	if (x > WIDTH / 2)
	{
		info->alpha += 0.1;
		if (info->alpha >= 360)
			info->alpha = 0;
	}
	if (x < WIDTH / 2)
	{
		info->alpha -= 0.1;
		if (info->alpha < 0)
			info->alpha = 359;
	}
	ft_mini_map(info, info->mlx, info->mlx_win);
	return 0;
}

int	mouse_hook(int key,  int x, int y, t_general *info)
{
	calcule_bite_ray(info);
	ft_dislay(info, info->mlx, info->mlx_win);
	(void)x;
	(void)y;
	// printf("Hello from key_hook! %d %d %d\n", x, y, key);
	if (key == 5)
		move_up(info, info->info_img);
	else if (key == 4)
		move_down(info, info->info_img);
	else if (key == 1)
		rotate_left(info);
	else if (key == 3)
		rotate_right(info);
	ft_mini_map(info, info->mlx, info->mlx_win);
	return (0);
}
int	close_win(int keycode, t_general *info)
{
	(void)info;
	(void)keycode;
	printf("closed by ESC! \n");
	exit(0);
}

void	display_pixel(t_general info)
{
	info.alpha = get_alpha_player(info);
	info.bita_ray = info.alpha;
	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "cub3d");
	info.info_img = malloc(sizeof(t_data));
	info.info_img->img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.info_img->addr = mlx_get_data_addr(info.info_img->img,
			&info.info_img->bits_per_pixel, &info.info_img->line_length,
			&info.info_img->endian);
	info.mini_map = malloc(sizeof(t_data));
	// info.mini_map->img = mlx_new_image(info.mlx, 300, 100);
	// info.mini_map->addr = mlx_get_data_addr(info.mini_map->img,
	// 		&info.mini_map->bits_per_pixel, &info.mini_map->line_length,
	// 		&info.mini_map->endian);
	get_texters(&info);
	ft_dislay(&info, info.mlx, info.mlx_win);	
	mlx_hook(info.mlx_win, 2, 3, key_hook, &info);
	// mlx_hook(info.mlx_win, 6, 1L<<6, mouse_hook_1, &info);
	mlx_mouse_hook(info.mlx_win, mouse_hook, &info);
	mlx_hook(info.mlx_win, 17, 0, close_win, &info);
	mlx_loop(info.mlx);
}
