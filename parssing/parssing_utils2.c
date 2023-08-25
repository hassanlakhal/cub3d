/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 03:47:09 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/25 12:56:15 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_list(t_general *info)
{
	info->map = NULL;
	info->bloc = NULL;
	info->number_of_line = 0;
}

char	*skip_line(int fd)
{
	char	*str;
	char	*temp;

	str = get_next_line(fd);
	while (str)
	{
		if (str && ft_strlen(str) > 1)
			break ;
		free(str);
		str = get_next_line(fd);
	}
	temp = NULL;
	if (str)
	{
		temp = ft_strdup(str);
		free(str);
	}
	return (temp);
}

void	ft_utils_read_lines_texter(t_general *info, char *str, char *file,
		int fd)
{
	int	i;

	i = 0;
	while (str)
	{
		file = ft_strjoin(file, str);
		if (info->number_of_line >= 6)
			break ;
		if (ft_strlen(str) > 1)
			info->number_of_line++;
		free(str);
		str = get_next_line(fd);
	}
	i = 0;
	if (ft_strlen(str) == 1)
	{
		if (str)
			free(str);
		str = skip_line(fd);
		i++;
	}
	if (i == 0)
		exit(1);
	info->bloc = ft_substr(file, 0, ft_strlen(file));
	(free(file), free(str));
}

void	read_lines_texter(t_general *info)
{
	int		i;
	char	*str;
	char	*file;
	int		fd;

	i = 0;
	fd = open(info->name_map, O_RDWR);
	init_list(info);
	str = skip_line(fd);
	file = NULL;
	info->bloc = NULL;
	ft_utils_read_lines_texter(info, str, file, fd);
	close(fd);
}

int	get_max_of_line(char **map)
{
	int	i;
	int	max_len;

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
