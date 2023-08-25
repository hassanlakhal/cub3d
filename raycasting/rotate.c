/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:06:52 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/25 13:07:07 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_right(t_general *info)
{
	info->alpha += SPEEDALPHA;
	if (info->alpha >= 360)
		info->alpha = 0;
}

void	rotate_left(t_general *info)
{
	info->alpha -= SPEEDALPHA;
	if (info->alpha < 0)
		info->alpha = 359;
}
