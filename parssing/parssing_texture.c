/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:00:03 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/27 04:56:51 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_rgb_val(char **rgb_val, t_general *info, int index)
{
	int	i;

	i = 0;
	while (rgb_val[i])
	{
		if (ft_strlen(rgb_val[i]) > 3 || ft_atoi(rgb_val[i]) > 255)
		{
			printf("15:ERROR\n");
			free_2d(rgb_val);
			exit(0);
		}
		i++;
	}
	info->info_rgb[index]._R = ft_atoi(rgb_val[0]);
	info->info_rgb[index]._G = ft_atoi(rgb_val[1]);
	info->info_rgb[index]._B = ft_atoi(rgb_val[2]);
	free_2d(rgb_val);
}

void	sub_parsing_1(t_general *info, t_bloc *data)
{
	int		i;
	int		cont;
	char	**valid_path;

	i = 0;
	cont = 0;
	while (i < data->bloc_size_texteur)
	{
		if (ft_block_texteurs(&info->info_texteur[i]) == 0)
			cont++;
		valid_path = ft_split(info->info_texteur[i].path, ' ');
		check_line(valid_path, PATH);
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
}
void	sub_parsing_2(t_general *info, t_bloc *data)
{
	int		i;
	int		cont;
	char	**valid_value_rgb;

	i = 0;
	cont = 0;
	while (i < data->bloc_size_rgb)
	{
		if (ft_block_rgb(&info->info_rgb[i]) == 0)
			cont++;
		cont_of_coma(info->info_rgb[i].rgb_value);
		info->info_rgb[i].rgb_value = reaplace(info->info_rgb[i].rgb_value, 1,
				',');
		valid_value_rgb = ft_split(info->info_rgb[i].rgb_value, ' ');
		check_line(valid_value_rgb, RGB);
		fill_rgb_val(valid_value_rgb, info, i);
		free(info->info_rgb[i].rgb_value);
		i++;
	}
	if (cont != data->bloc_size_rgb)
	{
		printf("7:ERROR\n");
		exit(0);
	}
}

void check_name_map(char *name)
{
	int	i;

	i = 0;
	while (name[i])
		i++;
	if (name[--i] != 'b' || name[--i] != 'u' || name[--i] != 'c'
		|| name[--i] != '.')
	{
		printf("Must be a .cub file\n");
		exit(1);
	}
}

char *get_name_map(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Invalid Arguments\n");
		exit(1);
	}
	check_name_map(av[1]);
	return ft_strdup(av[1]);
}

t_general	*ft_parssing(int ac, char **av)
{
	t_general	*info;
	t_bloc		*data;

	info = malloc(sizeof(t_general));
	if (!info)
		return (NULL);
	data = malloc(sizeof(t_bloc) * 6);
	if (!data)
		return (NULL);
	info->name_map = get_name_map(ac, av);
	read_lines_texter(info);
	ft_bloc(info, data);
	sub_parsing_1(info, data);
	sub_parsing_2(info, data);
	free(data);
	return (info);
	// clear_all(info, data->bloc_size_texteur, data->bloc_size_rgb);
}
