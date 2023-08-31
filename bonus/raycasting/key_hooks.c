/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:35:01 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/31 11:23:51 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mouse_hook_1(int x, int y, t_general *info)
{
	if (info->mouse_x == x || x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (0);
	calcule_bite_ray(info);
	ft_dislay(info, info->mlx, info->mlx_win);
	if (x > (WIDTH / 2))
	{
		info->alpha += 0.4;
		if (info->alpha >= 360)
			info->alpha = 0;
	}
	if (x < (WIDTH / 2))
	{
		info->alpha -= 0.4;
		if (info->alpha < 0)
			info->alpha = 360;
	}
	ft_mini_map(info, info->mlx, info->mlx_win);
	info->mouse_x = x;
	return (0);
}

int	key_hook(int key, t_general *info)
{
	if (key == 65307)
	{
		printf("closed by ESC!\n");
		exit(0);
	}
	else if (key == 119)
		move_up(info, info->info_img);
	else if (key == 115)
		move_down(info, info->info_img);
	else if (key == 97)
		move_right(info, info->info_img);
	else if (key == 100)
		move_left(info, info->info_img);
	else if (key == 65361)
		rotate_left(info);
	else if (key == 65363)
		rotate_right(info);
	return (0);
}

int	mouse_hook(int key, int x, int y, t_general *info)
{
	calcule_bite_ray(info);
	ft_dislay(info, info->mlx, info->mlx_win);
	(void)x;
	(void)y;
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
	printf("closed !\n");
	exit(0);
}

int	mouse(void *param)
{
	t_general	*info;
	int			x;
	int			y;

	info = (t_general *)param;
	x = 0;
	y = 0;
	mlx_mouse_get_pos(info->mlx, info->mlx_win, &x, &y);
	mouse_hook_1(x, y, info);
	return (0);
}
