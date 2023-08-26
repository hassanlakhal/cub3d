/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:21:49 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/26 11:42:10 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_alpha_player(t_general info)
{
	if (info.info_player->direction == 'N')
		return (270);
	if (info.info_player->direction == 'E')
		return (0);
	if (info.info_player->direction == 'S')
		return (90);
	if (info.info_player->direction == 'W')
		return (180);
	return (0);
}

void	get_texters(t_general *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		info->info_texteur[i].texteur = malloc(sizeof(t_data));
		if (!info->info_texteur[i].texteur)
		return ;
		info->info_texteur[i].texteur->img = mlx_xpm_file_to_image(info->mlx,
				info->info_texteur[i].path,
				&info->info_texteur[i].texteur->width,
				&info->info_texteur[i].texteur->height);
		if (!info->info_texteur[i].texteur->img)
		{
			printf("image not found!");
			exit(2);
		}
		info->info_texteur[i].texteur->addr = mlx_get_data_addr(
				info->info_texteur[i].texteur->img,
				&info->info_texteur[i].texteur->bits_per_pixel,
				&info->info_texteur[i].texteur->line_length,
				&info->info_texteur[i].texteur->endian);
		i++;
	}
}
