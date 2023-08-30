/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:33:48 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/30 14:44:19 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_top_buttom_wall(char **map, int y)
{
	int	i;
	int	cont_top;
	int	cont_buttom;

	i = 0;
	cont_top = 0;
	cont_buttom = 0;
	while (map[0][i])
	{
		if (map[0][i] == '1' || map[0][i] == ' ')
			cont_top++;
		i++;
	}
	i = 0;
	while (map[y - 1][i])
	{
		if (map[y - 1][i] == '1' || map[y - 1][i] == ' ')
			cont_buttom++;
		i++;
	}
	if ((int)ft_strlen(map[y - 1]) != cont_buttom
		|| (int)ft_strlen(map[0]) != cont_top)
		(printf("ERROR\nProblem in wall\n"), exit(1));
}

void	check_side_wall(char **map, int y)
{
	int	i;
	int	cont_side;

	i = 1;
	cont_side = 0;
	while (map[i])
	{
		if (map[i][0] == '1' || map[i][0] == ' ')
			cont_side++;
		i++;
	}
	if (cont_side != y - 1)
		(printf("ERROR\nProblem in wall\n"), exit(1));
}

void	postion_of_player(char **map, t_general *data)
{
	int	i;
	int	j;
	int	cont;

	j = 0;
	i = 0;
	cont = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NEWS", map[i][j]))
			{
				data->info_player->pos_x = j + 0.5;
				data->info_player->pos_y = i + 0.5;
				data->info_player->direction = map[i][j];
				cont++;
			}
			j++;
		}
		i++;
	}
	if (cont != 1)
		(printf("ERROR\nproblem in palyer\n"), exit(1));
}

char	**dup_str_2d(char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = malloc(sizeof(char *) * (ft_strlen_2d(tab) + 1));
	if (!new_tab)
		return (NULL);
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

t_general	*ft_parssing_map(t_general *data)
{
	char	**map;
	char	**dup_map;

	data->info_player = malloc(sizeof(t_player));
	if (!data->info_player)
		return (NULL);
	get_map(data);
	check_dobule_new_line(data->map);
	map = ft_split(data->map, '\n');
	dup_map = ft_split(data->map, '\n');
	check_top_buttom_wall(map, ft_strlen_2d(map));
	check_wall(map, ft_strlen_2d(map));
	check_side_wall(map, ft_strlen_2d(map));
	framing_map(map, dup_map);
	postion_of_player(map, data);
	data->dimensions[0] = ft_strlen(map[0]);
	data->dimensions[1] = ft_strlen_2d(map);
	floodfile(dup_map, *(data));
	free_2d(dup_map);
	if (data->map)
		free(data->map);
	data->valid_map = dup_str_2d(map);
	free_2d(map);
	return (data);
}
