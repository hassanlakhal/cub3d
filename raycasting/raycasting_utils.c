/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:17:29 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/27 06:17:57 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_color(t_general *info, char c)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (info->info_rgb[i].type_color[0] == c)
			return (rgbToHex(info->info_rgb[i]._R, info->info_rgb[i]._G,
					info->info_rgb[i]._B));
		i++;
	}
	return (0);
}

t_data	*get_side_texteur(t_general *info, char *str)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(str, info->info_texteur[i].direction, 2))
			return (info->info_texteur[i].texteur);
		i++;
	}
	return (info->info_texteur[0].texteur);
}

void	calcule_of_wall(t_general *info, int i, t_coordinates *start)
{
	double	projec;

	info->v = vertecal(info, info->bita_ray);
	info->h = horizontal(info, info->bita_ray);
	projec = calcule_projection(info);
	start->i = i;
	info->end->i = i;
	info->wall_hight = ((projec * 45) / (fmin(info->v->lenght, info->h->lenght)
				* cos(((info->bita_ray - info->alpha) * PI) / 180)));
	start->j = (HEIGHT / 2) - info->wall_hight / 2;
	start->j *= start->j > 0;
	info->end->j = (HEIGHT / 2) + info->wall_hight / 2;
	if (info->end->j > HEIGHT)
		info->end->j = HEIGHT;
}

void	calcule_bite_ray(t_general *info)
{
	int		i;
	double	temp;

	info->bita_ray = info->alpha;
	i = 0;
	temp = 60 / ((double)WIDTH);
	while (i < (WIDTH) / 2)
	{
		if (info->bita_ray <= 0)
			info->bita_ray = 360;
		info->bita_ray -= temp;
		i++;
	}
}