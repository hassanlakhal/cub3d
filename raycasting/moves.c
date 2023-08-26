/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:59:27 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/26 12:14:12 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_up(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x + cos((info->alpha * PI) / 180) * SPEED;
	pos_y = info->info_player->pos_y + sin((info->alpha * PI) / 180) * SPEED;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	ft_dislay(info, info->mlx, info->mlx_win);

}

void	move_down(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x - cos((info->alpha * PI) / 180) * SPEED;
	pos_y = info->info_player->pos_y - sin((info->alpha * PI) / 180) * SPEED;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	ft_dislay(info, info->mlx, info->mlx_win);

}

void	move_left(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x + cos(((info->alpha - 270) * PI) / 180)
		* (SPEED - 0.05);
	pos_y = info->info_player->pos_y + sin(((info->alpha - 270) * PI) / 180)
		* (SPEED - 0.05);
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	ft_dislay(info, info->mlx, info->mlx_win);

}

void	move_right(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x - cos(((info->alpha + 90) * PI) / 180)
		* (SPEED - 0.05);
	pos_y = info->info_player->pos_y - sin(((info->alpha + 90) * PI) / 180)
		* (SPEED - 0.05);
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	ft_dislay(info, info->mlx, info->mlx_win);

}
