/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:37:46 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/12 00:54:20 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	clear_all(t_general *data, int a, int b)
{
	int	i;

	i = 0;
	while (i < a)
	{
		free(data->info_texteur[i].path);
		free(data->info_texteur[i].direction);
		i++;
	}
	i = 0;
	while (i < b)
	{
		free(data->info_rgb[i].type_color);
		free(data->info_rgb[i].rgb_value);
		i++;
	}
	free(data->info_texteur);
	free(data->info_rgb);
	free(data->bloc);
	free(data);
}
