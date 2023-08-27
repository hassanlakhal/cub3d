/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:37:46 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/27 06:04:48 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	clear_all(t_general *data)
{
	int	i;

	i = 0;
	while (i < data->bloc_s->bloc_size_texteur)
	{
		free(data->info_texteur[i].path);
		data->info_texteur[i].path = NULL;
		free(data->info_texteur[i].direction);
		data->info_texteur[i].direction = NULL;
		free(data->info_texteur[i].texteur);
		data->info_texteur[i].texteur = NULL;
		i++;
	}
	i = 0;
	while (i < data->bloc_s->bloc_size_rgb)
	{
		free(data->info_rgb[i].type_color);
		data->info_rgb[i].type_color = NULL;
		i++;
	}
	free(data->info_texteur);
	data->info_texteur = NULL;
	free(data->info_rgb);
	data->info_rgb = NULL;
	free(data->bloc_s);
	data->bloc_s = NULL;
	free(data->name_map);
	data->name_map = NULL;
	free_2d(data->valid_map);
	data->valid_map =NULL;
	free(data->bloc);
	free(data->info_player);
	free(data->info_img);
	// free(data);
	//free(data->name_map);
}
