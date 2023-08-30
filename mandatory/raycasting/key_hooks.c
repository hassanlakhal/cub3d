/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:35:01 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/30 16:00:15 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_hook(int key, t_general *info)
{
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
	return (0);
}

int	close_win(int keycode, t_general *info)
{
	(void)info;
	(void)keycode;
	printf("closed by ESC! \n");
	exit(0);
}
