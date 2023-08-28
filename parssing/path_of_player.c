/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_of_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:07:32 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/28 01:21:04 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*dupchar(char c)
{
	char	*f_dupchar;

	f_dupchar = malloc(2);
	if (!f_dupchar)
		return (NULL);
	f_dupchar[0] = c;
	f_dupchar[1] = '\0';
	return (f_dupchar);
}

char	*ft_charjoin(char *str, char c, int number, int max_len)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = malloc(ft_strlen(str) + number + 1);
	if (!str)
		return (dupchar(c));
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (i < max_len)
	{
		new_str[i] = c;
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

void	framing_map(char **map, char **dup_map)
{
	int	i;
	int	max_len;
	int	len;

	i = 0;
	max_len = get_max_of_line(map);
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < max_len)
		{
			map[i] = ft_charjoin(map[i], 32, max_len - len, max_len);
			dup_map[i] = ft_charjoin(dup_map[i], 32, max_len - len, max_len);
		}
		i++;
	}
}

void	flood(char **map, t_general info, int x, int y)
{
	if (x < 0 || y < 0 || x > info.dimensions[0] || y > info.dimensions[1])
		return ;
	if (map[y][x] == ' ')
	{
		printf("ERROR\nmap is open to empty space\n");
		exit(0);
	}
	if (map[y][x] == '1' || map[y][x] == 'x')
		return ;
	if (ft_strchr("NEWS0", map[y][x]))
	{
		map[y][x] = 'x';
		flood(map, info, x, y + 1);
		flood(map, info, x + 1, y);
		flood(map, info, x, y - 1);
		flood(map, info, x - 1, y);
	}
}

void	floodfile(char **map, t_general info)
{
	flood(map, info, info.info_player->pos_x, info.info_player->pos_y);
}
