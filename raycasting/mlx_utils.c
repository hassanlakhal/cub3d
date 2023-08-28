/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:57:25 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/28 01:21:04 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_general *info, int x, int y, int color)
{
	char	*dst;

	dst = info->info_img->addr + (y * info->info_img->line_length + x
			* (info->info_img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_get_pixel(t_data *texteur, int x, int y)
{
	char	*dst;

	dst = texteur->addr + (y * texteur->line_length + x
			* (texteur->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
