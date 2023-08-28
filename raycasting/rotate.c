/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:06:52 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/28 01:21:04 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_right(t_general *info)
{
	info->alpha += SPEEDALPHA;
	if (info->alpha >= 360)
		info->alpha = 0;
	ft_dislay(info, info->mlx, info->mlx_win);
}

void	rotate_left(t_general *info)
{
	info->alpha -= SPEEDALPHA;
	if (info->alpha < 0)
		info->alpha = 359;
	ft_dislay(info, info->mlx, info->mlx_win);
}
