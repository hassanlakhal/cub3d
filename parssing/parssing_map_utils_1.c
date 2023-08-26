/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_map_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:32:18 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/26 11:32:35 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	utils_get_map(char *str, int fd)
{
	int	i;
 
	i = 0;
	while (str && i < 6)
	{
		if (str && ft_strlen(str) > 1)
			i++;
		free(str);
		str = get_next_line(fd);
	}
	if (str)
		free(str);
}

void	get_map(t_general *info)
{
	int		fd;
	char	*str;
	char	*map;

	fd = open(info->name_map, O_RDWR);
	if (fd == -1)
	{
		perror(info->name_map);
		exit(1);
	}
	str = get_next_line(fd);
	map = NULL;
	utils_get_map(str, fd);
	str = skip_line(fd);
	while (str)
	{
		map = ft_strjoin(map, str);
		free(str);
		str = get_next_line(fd);
	}
	info->map = ft_strdup(map);
	free(map);
	close(fd);
}

void	check_dobule_new_line(char *str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			break ;
		i++;
	}
	while (str[i] && str[i] == '\n')
		i++;
	len = ft_strlen(str);
	if (len != i)
	{
		printf("19:ERROR\n");
		exit(1);
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
			if (str[i][ft_strlen(str[i]) - 1] != '1' && str[i][ft_strlen(str[i])
				- 1] != '\t' && str[i][ft_strlen(str[i]) - 1] != ' ')
			{
				printf("16:ERROR\n");
				exit(0);
			}
			else if (!ft_strchr("NEWS10 ", str[i][j]))
			{
				printf("17:ERROR invalid c\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}
