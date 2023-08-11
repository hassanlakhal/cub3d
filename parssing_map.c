/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:33:48 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/11 04:14:48 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map(t_general *info)
{
	int		fd;
	int		i;
	char	*str;
	char	*map;

	fd = open("map/map.cub", O_RDWR);
	str = get_next_line(fd);
	map = NULL;
	i = 0;
	while (str && i < 6)
	{
		if (str && ft_strlen(str) > 1)
			i++;
		free(str);
		str = get_next_line(fd);
	}
	str = skip_line(fd);
	while (str)
	{
		map = ft_strjoin(map, str);
		free(str);
		str = get_next_line(fd);
	}
	info->map = ft_strdup(map);
	close(fd);
}

void	check_dobule_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			printf("ERROR\n");
			exit(0);
		}
		i++;
	}
}

void	check_wall(char **str, int y)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] && i < y)
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][ft_strlen(str[i]) - 1] != '1')
			{
				printf("16:ERROR\n");
				exit(0);
			}
			else if (!ft_strchr("NEWS10 	", str[i][j]))
			{
				printf("17:ERROR\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void check_top_buttom_wall(char **map, int y)
{
	int	i;
	int	cont_top;
	int	cont_buttom;

	i = 0;
	cont_top = 0;
	cont_buttom = 0;
	while (map[0][i])
	{
		if (map[0][i] == '1')
			cont_top++;
		i++;
	}
	i = 0;
	while (map[y - 1][i])
	{
		if (map[y - 1][i] == '1')
			cont_buttom++;
		i++;
	}
	if ((int)ft_strlen(map[y - 1])  != cont_buttom ||(int)ft_strlen(map[0]) != cont_top)
		(printf("18:ERROR\n"),exit(0));
}

void check_side_wall(char **map, int y)
{
	int i;
	int cont_side;

	i = 1;
	cont_side = 0;
	while (map[i])
	{
		if (map[i][0] == '1')
			cont_side++;
		i++;
	}
	if (cont_side != y - 1)
		(printf("18:ERROR\n"),exit(0));
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
				data->info_player->pos_x = j;
				data->info_player->pos_y = i;
				cont++;
			}
			j++;
		}
		i++;
	}
	if (cont != 1)
		(printf("17:ERROR\n"), exit(0));
}

t_general	*ft_parssing_map(t_general *data)
{
	int		i;
	char	**map;

	i = 0;
	data->info_player = malloc(sizeof(t_player));
	get_map(data);
	check_dobule_new_line(data->map);
	map = ft_split(data->map, '\n');
	check_top_buttom_wall(map, ft_strlen_2d(map));
	check_wall(map, ft_strlen_2d(map));
	check_side_wall(map, ft_strlen_2d(map));
	postion_of_player(map, data);
	printf("x:%d\ty:%d", data->info_player->pos_x, data->info_player->pos_y);
	return (data);
}
