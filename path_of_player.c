/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_of_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:07:32 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/23 00:42:58 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_max_of_line(char **map)
{
	int i;
	int max_len;

	i = 0;
	max_len = ft_strlen(map[0]);
	while (map[i])
	{
		if (max_len < (int)ft_strlen(map[i]))
			max_len = (int)ft_strlen(map[i]);
		i++;
	}
	return (max_len);
}
char *dupchar(char c)
{
	char *_dupchar;

	_dupchar = malloc(2);
	_dupchar[0] = c;
	_dupchar[1] = '\0';
	return (_dupchar);
}

char *ft_charjoin(char *str, char c, int number, int max_len)
{
	int i;
	char *new_str;

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

void framing_map(char **map, char **dup_map)
{
	int i;
	int max_len;
	int len;

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

void flood(char **map, t_general info, int x, int y)
{
	if (x < 0 || y < 0 || x > info.dimensions[0] || y > info.dimensions[1])
		return;
	if (map[y][x] == ' ')
	{
		printf("Error\n");
		exit(0);
	}
	if (map[y][x] == '1' || map[y][x] == 'x')
		return;
	if (ft_strchr("NEWS0", map[y][x]))
	{
		map[y][x] = 'x';
		flood(map, info, x, y + 1);
		flood(map, info, x + 1, y);
		flood(map, info, x, y - 1);
		flood(map, info, x - 1, y);
	}
}

void floodfile(char **map, t_general info)
{
	flood(map, info, info.info_player->pos_x, info.info_player->pos_y);
}
