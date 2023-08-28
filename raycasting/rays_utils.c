/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:09:32 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/28 02:35:54 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	break_wall(t_general *info, int x, int y)
{
	if (x < 0 || x >= info->dimensions[0])
		return (false);
	if (y < 0 || y >= info->dimensions[1])
		return (false);
	if (info->valid_map[y][x] == '1' || info->valid_map[y][x] == 32)
		return (false);
	return (true);
}

void	step_rays(t_general *info, double *x_steps, double *y_steps,
		double beta)
{
	double	atan;

	atan = -1 / tan(((beta) * PI) / 180);
	info->start->i = info->info_player->pos_x * 45;
	info->start->j = info->info_player->pos_y * 45;
	if (beta > 180)
	{
		info->end->j = ((int)(info->start->j / 45) * 45) - 0.0001;
		info->end->i = info->start->i + (info->start->j - info->end->j) * atan;
		(*y_steps) = -45;
		(*x_steps) = -(*y_steps) * atan;
	}
	if (beta < 180)
	{
		info->end->j = ((int)(info->start->j / 45) * 45) + 45;
		info->end->i = info->start->i + (info->start->j - info->end->j) * atan;
		(*y_steps) = 45;
		(*x_steps) = -(*y_steps) * atan;
	}
}

void	set_len(t_general *info, t_casted_ray *h)
{
	double	l;

	l = sqrt(pow(info->end->i - info->start->i, 2) + pow(info->end->j
				- info->start->j, 2));
	h->lenght = l;
	h->end.i = info->end->i;
	h->end.j = info->end->j;
}

void	step_rays_v(t_general *info, double *x_steps, double *y_steps,
		double beta)
{
	double	atan;

	atan = -tan(((beta) * PI) / 180);
	info->start->i = info->info_player->pos_x * 45;
	info->start->j = info->info_player->pos_y * 45;
	if (beta > 90 && beta < 270)
	{
		info->end->i = ((int)(info->start->i / 45) * 45) - 0.0001;
		info->end->j = info->start->j + (info->start->i - info->end->i) * atan;
		(*x_steps) = -45;
		(*y_steps) = -(*x_steps) * atan;
	}
	if (beta < 90 || beta > 270)
	{
		info->end->i = ((int)(info->start->i / 45) * 45) + 45;
		info->end->j = info->start->j + (info->start->i - info->end->i) * atan;
		(*x_steps) = 45;
		(*y_steps) = -(*x_steps) * atan;
	}
}

double	calcule_projection(t_general *info)
{
	int	half_width;

	(void)info;
	half_width = WIDTH / 2;
	return (half_width / tan((30 * PI) / 180));
}
