/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_texture_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:38:04 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/25 11:38:54 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	ft_fill_info_1(t_bloc *line, t_general *info_bloc)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < 6)
	{
		if (line[i].type == PATH && j < line->bloc_size_texteur)
		{
			info_bloc->info_texteur[j].direction = ft_strdup(line[i].val_1);
			info_bloc->info_texteur[j].path = ft_strdup(line[i].val_2);
			(free(line[i].val_2), free(line[i].val_1));
			j++;
		}
		i++;
	}
}
void	ft_fill_info_2(t_bloc *line, t_general *info_bloc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 6)
	{
		if (line[i].type == RGB && j < line->bloc_size_rgb)
		{
			info_bloc->info_rgb[j].type_color = ft_strdup(line[i].val_1);
			info_bloc->info_rgb[j].rgb_value = ft_strdup(line[i].val_2);
			(free(line[i].val_2), free(line[i].val_1));
			j++;
		}
		i++;
	}
}

void	ft_fill_info(t_bloc *line, t_general *info_bloc)
{
	info_bloc->info_texteur = malloc(sizeof(t_texteur)
			* line->bloc_size_texteur);
	info_bloc->info_rgb = malloc(sizeof(t_rgb_info) * line->bloc_size_rgb);
	ft_fill_info_1(line, info_bloc);
	ft_fill_info_2(line, info_bloc);
}

void	ft_bloc(t_general *data, t_bloc *data_of_texture)
{
	int		i;
	char	**textures;
	char	**info;

	if (data->number_of_line != 6)
		(free(data->bloc), printf("4:ERROR\n"), exit(0));
	textures = ft_split(data->bloc, '\n');
	i = 0;
	while (i < data->number_of_line)
	{
		if (textures[i] && ft_strchr(textures[i], '\t'))
			textures[i] = reaplace(textures[i], 4, '\t');
		info = ft_split_pos(textures[i], ' ', 1);
		data_of_texture[i].val_1 = ft_strdup(info[0]);
		data_of_texture[i].val_2 = ft_strdup(info[1]);
		free_2d(info);
		i++;
	}
	check_direction(data_of_texture);
	type_of_bloc(data_of_texture);
	ft_fill_info(data_of_texture, data);
	free_2d(textures);
}

int	ft_block_texteurs(t_texteur *bloc_1)
{
	if (bloc_1->direction && (!ft_strncmp(bloc_1->direction, "NO", 2)
			|| !ft_strncmp(bloc_1->direction, "SO", 2)
			|| !ft_strncmp(bloc_1->direction, "WE", 2)
			|| !ft_strncmp(bloc_1->direction, "EA", 2)))
		return (0);
	else
		return (1);
}