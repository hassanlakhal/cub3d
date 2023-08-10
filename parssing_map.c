/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:33:48 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/11 00:51:17 by hlakhal-         ###   ########.fr       */
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
				printf("%d   16:ERROR\n", i);
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

t_general	*ft_parssing_map(t_general *data)
{
	int		i;
	char	**map;

	i = 0;
	get_map(data);
	check_dobule_new_line(data->map);
	map = ft_split(data->map, '\n');
	check_wall(map, ft_strlen_2d(map));
	return (data);
}
