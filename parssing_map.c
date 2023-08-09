/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:33:48 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/09 21:30:35 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"


void ft_bloc_map()
{
	int fd;
	int i;
	char *str ;
	char *map;

	fd = open("map/map.cub",O_RDWR);
	str = get_next_line(fd);
	map = NULL;
	i  = 0;
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
		map = ft_strjoin(map,str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	printf("%s",map);
}
