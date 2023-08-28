/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:59:27 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/28 16:17:07 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	protect_from_wall(t_general *info, double pos_x, double pos_y)
{
	if (((int)pos_y + 1 >= info->dimensions[1]) || ((int)pos_x - 1 >= info->dimensions[0]) || (pos_x < 0) || (pos_y < 0))
		return 1;
	if (((int)pos_x != 1 && (info->valid_map[(int)pos_y][(int)pos_x - 1] == '1' || info->valid_map[(int)pos_y][(int)pos_x - 1] == 32)) 
		&&((info->valid_map[(int)pos_y + 1][(int)pos_x] == '1' || info->valid_map[(int)pos_y + 1][(int)pos_x] == 32)))
		return 1;
	return 0;
}
void	move_up(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	(void)img;
	pos_x = info->info_player->pos_x + cos((info->alpha * PI) / 180) * SPEED;
	pos_y = info->info_player->pos_y + sin((info->alpha * PI) / 180) * SPEED;
	if (protect_from_wall(info, pos_x, pos_y))
		return ;
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
	if (protect_from_wall(info, pos_x, pos_y))
		return ;
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
	if (protect_from_wall(info, pos_x, pos_y))
		return ;
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
	if (protect_from_wall(info, pos_x, pos_y))
		return ;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	ft_dislay(info, info->mlx, info->mlx_win);
}
