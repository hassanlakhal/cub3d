/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:59:27 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/29 16:23:25 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	slide_player(t_general *info, double pos_x, double pos_y)
{
	if (info->alpha != 270.00 && info->alpha != 90 && info->alpha != 180 && info->alpha != 0)
	{
		if (info->valid_map[(int)info->info_player->pos_y][(int)pos_x] != '1'
			&& info->valid_map[(int)info->info_player->pos_y][(int)pos_x] != 32)
			{
				// printf("%f\t%f\n", (pos_x * cos(((info->alpha) * PI) / 180)), pos_x);
				info->info_player->pos_x = pos_x;
			}
		if (info->valid_map[(int)pos_y][(int)info->info_player->pos_x] != '1'
			&& info->valid_map[(int)pos_y][(int)info->info_player->pos_x] != 32)
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
	if (info->valid_map[(int)pos_y][(int)info->info_player->pos_x] == '1'
		&& info->valid_map[(int)info->info_player->pos_y][(int)pos_x] == '1')
		return ;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32 )
	{
		printf("%f %f\n",fmin(info->h->lenght, info->h->lenght), fabs(30  * cos(((info->alpha - info->bita_ray) * PI)/ 180)));
		
		if (info->h->lenght >=  fabs(30 * cos(((info->alpha - info->bita_ray) * PI)/ 180))  && info->v->lenght >=  fabs(30 * cos(((info->alpha - info->bita_ray) * PI)/ 180))) 
		{
			info->info_player->pos_x = pos_x;
			info->info_player->pos_y = pos_y;
		}
		else
			slide_player(info, pos_x, pos_y);
		// if (fmin(info->h->lenght, info->h->lenght) <= 15)
		// {
		// 	printf("in front of wall\n");
		// 	return ;
		// }
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
	if (info->valid_map[(int)pos_y][(int)info->info_player->pos_x] == '1'
		&& info->valid_map[(int)info->info_player->pos_y][(int)pos_x] == '1')
		return ;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
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
	if (info->valid_map[(int)pos_y][(int)info->info_player->pos_x] == '1'
		&& info->valid_map[(int)info->info_player->pos_y][(int)pos_x] == '1')
		return ;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
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
	if (info->valid_map[(int)pos_y][(int)info->info_player->pos_x] == '1'
		&& info->valid_map[(int)info->info_player->pos_y][(int)pos_x] == '1')
		return ;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1'
		&& info->valid_map[(int)pos_y][(int)pos_x] != 32)
	{
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	else
		slide_player(info, pos_x, pos_y);
	ft_dislay(info, info->mlx, info->mlx_win);
}
