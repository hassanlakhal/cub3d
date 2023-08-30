/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:00:03 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/30 17:08:54 by rlarabi          ###   ########.fr       */
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
			printf("ERROR\nEnter a bound 3 values between 0 - 255");
			free_2d(rgb_val);
			exit(1);
		}
		i++;
	}
	info->info_rgb[index]._r = ft_atoi(rgb_val[0]);
	info->info_rgb[index]._g = ft_atoi(rgb_val[1]);
	info->info_rgb[index]._b = ft_atoi(rgb_val[2]);
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
		printf("ERROR\nInvalide direction\n");
		exit(1);
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
		printf("ERROR\nlines of RGB more 2 lines\n");
		exit(1);
	}
}

char	*get_name_map(int ac, char **av)
{
	if (ac != 2)
	{
		printf("ERROR\nInvalid Arguments\n");
		exit(1);
	}
	check_name_map(av[1]);
	return (ft_strdup(av[1]));
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
}
