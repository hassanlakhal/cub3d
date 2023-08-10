/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:00:03 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/10 03:53:27 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	type_of_bloc(t_bloc *lines)
{
	int	i;

	i = 0;
	lines->bloc_size_texteur = 0;
	lines->bloc_size_rgb = 0;
	while (i < 6)
	{
		if (ft_strlen(lines[i].val_1) == 2)
		{
			lines[i].type = PATH;
			lines->bloc_size_texteur++;
		}
		else if (ft_strlen(lines[i].val_1) == 1)
		{
			lines[i].type = RGB;
			lines->bloc_size_rgb++;
		}
		else
			lines[i].type = 0;
		i++;
	}
}

void	ft_fill_info(t_bloc *line, t_general *info_bloc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	info_bloc->info_texteur = malloc(sizeof(t_texteur)
			* line->bloc_size_texteur);
	info_bloc->info_rgb = malloc(sizeof(t_rgb_info) * line->bloc_size_rgb);
	while (i < 6)
	{
		if (line[i].type == PATH && j < line->bloc_size_texteur)
		{
			info_bloc->info_texteur[j].direction = ft_strdup(line[i].val_1);
			info_bloc->info_texteur[j].path = ft_strdup(line[i].val_2);
			free(line[i].val_2);
			free(line[i].val_1);
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (i < 6)
	{
		if (line[i].type == RGB && j < line->bloc_size_rgb)
		{
			info_bloc->info_rgb[j].type_color = ft_strdup(line[i].val_1);
			info_bloc->info_rgb[j].rgb_value = ft_strdup(line[i].val_2);
			free(line[i].val_2);
			free(line[i].val_1);
			j++;
		}
		i++;
	}
	//free(line);
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
			textures[i] = reaplace(textures[i], 4);
		info = ft_split_pos(textures[i], ' ', 1);
		data_of_texture[i].val_1 = ft_strdup(info[0]);
		data_of_texture[i].val_2 = ft_strdup(info[1]);
		printf("%s\n", info[0]);
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

int	ft_block_rgb(t_rgb_info *bloc_2)
{
	if (bloc_2->type_color && (!ft_strncmp(bloc_2->type_color, "C", 2)
			|| !ft_strncmp(bloc_2->type_color, "F", 2)))
		return (0);
	else
		return (1);
}

void	ft_parssing(void)
{
	t_general	*info;
	t_bloc		*data;
	char		**valid_path;
	static int	cont;
	int			i;

	info = malloc(sizeof(t_general));
	data = malloc(sizeof(t_bloc) * 6);
	read_lines_texter(info);
	ft_bloc(info, data);
	i = 0;
	while (i < data->bloc_size_texteur)
	{
		if (ft_block_texteurs(&info->info_texteur[i]) == 0)
			cont++;
		valid_path = ft_split(info->info_texteur[i].path, ' ');
		check_line(valid_path);
		if (info->info_texteur[i].path)
			free(info->info_texteur[i].path);
		info->info_texteur[i].path = ft_strdup(valid_path[0]);
		free_2d(valid_path);
		i++;
	}
	if (cont != data->bloc_size_texteur)
	{
		printf("7:ERROR\n");
		exit(0);
	}
	//clear_all(info, data->bloc_size_texteur, data->bloc_size_rgb);
}
