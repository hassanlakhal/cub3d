/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:59:27 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/30 02:53:27 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	direction_of_palyer(t_general *info)
{
	if (info->alpha > 0 && info->alpha < 90)
	{
		info->direction_palyer.x = 1;
		info->direction_palyer.y = 1;
	}
	else if (info->alpha > 90 && info->alpha < 180)
	{
		info->direction_palyer.x = -1;
		info->direction_palyer.y = 1;
	}
	else if (info->alpha > 180 && info->alpha < 270)
	{
		info->direction_palyer.x = -1;
		info->direction_palyer.y = -1;
	}
	else if (info->alpha > 270 && info->alpha < 360)
	{
		info->direction_palyer.x = 1;
		info->direction_palyer.y = -1;
	}
	else if (info->alpha == 270)
	{
		info->direction_palyer.y = 1;
		info->direction_palyer.x = 0;
	}
	else if (info->alpha == 0)
	{
		info->direction_palyer.y = 0;
		info->direction_palyer.x = 1;
	}
	else if (info->alpha == 90)
	{
		info->direction_palyer.y = -1;
		info->direction_palyer.x = 0;
	}
	else if (info->alpha == 180)
	{
		info->direction_palyer.y = 0;
		info->direction_palyer.x = -1;
	}
}

void	slide_player(t_general *info, double pos_x, double pos_y)
{
	if (info->alpha != 270.00 && info->alpha != 90 && info->alpha != 180
		&& info->alpha != 0)
	{
		if (info->valid_map[(int)info->info_player->pos_y][(int)(pos_x + (SPEED
					* info->direction_palyer.x))] != '1'
			&& info->valid_map[(int)info->info_player->pos_y][(int)(pos_x
				+ (SPEED * info->direction_palyer.x))] != 32)
		{
			info->info_player->pos_x = pos_x;
		}
		if (info->valid_map[(int)(pos_y + (SPEED
					* info->direction_palyer.y))][(int)info->info_player->pos_x] != '1'
			&& info->valid_map[(int)(pos_y + (SPEED
					* info->direction_palyer.y))][(int)info->info_player->pos_x] != 32)
			info->info_player->pos_y = pos_y;
	}
}

void	move_up(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x + cos((info->alpha * PI) / 180) * SPEED;
	pos_y = info->info_player->pos_y + sin((info->alpha * PI) / 180) * SPEED;
	direction_of_palyer(info);
	if (info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)info->info_player->pos_x] == '1'
		&& info->valid_map[(int)info->info_player->pos_y][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] == '1')
		return ;
	if (info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] != '1'
		&& info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	else
		slide_player(info, pos_x, pos_y);
	ft_dislay(info, info->mlx, info->mlx_win);
}

void	move_down(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x - cos((info->alpha * PI) / 180) * SPEED;
	pos_y = info->info_player->pos_y - sin((info->alpha * PI) / 180) * SPEED;
	direction_of_palyer(info);
	if (info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)info->info_player->pos_x] == '1'
		&& info->valid_map[(int)info->info_player->pos_y][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] == '1')
		return ;
	if (info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] != '1'
		&& info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	else
		slide_player(info, pos_x, pos_y);
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
		direction_of_palyer(info);
	if (info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)info->info_player->pos_x] == '1'
		&& info->valid_map[(int)info->info_player->pos_y][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] == '1')
		return ;
	if (info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] != '1'
		&& info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	else
		slide_player(info, pos_x, pos_y);
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
	direction_of_palyer(info);
	if (info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)info->info_player->pos_x] == '1'
		&& info->valid_map[(int)info->info_player->pos_y][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] == '1')
		return ;
	if (info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] != '1'
		&& info->valid_map[(int)(pos_y + (SPEED
				* info->direction_palyer.y))][(int)(pos_x + (SPEED
				* info->direction_palyer.x))] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	else
		slide_player(info, pos_x, pos_y);
	ft_dislay(info, info->mlx, info->mlx_win);
}
