/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:00:03 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/09 18:53:57 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	form_of_file(int fd)
{
	int		cont;
	int		a;
	char	*str;

	cont = 0;
	fd = open("map/map.cub", O_RDWR);
	str = get_next_line(fd);
	while (str)
	{
		if (str && ft_strlen(str) > 1 && a)
		{
			a = 0;
			cont++;
		}
		if (str && !ft_strncmp(str, "\n", 1) && str[0] == '\n')
			a = 1;
		free(str);
		str = get_next_line(fd);
	}
	printf("%d\n",cont);
	if (cont > 7)
		(printf("0:ERROR\n"), close(fd), exit(0));
	free(str);
	close(fd);
}

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

void	read_lines_texter(t_general *info)
{
	int		i;
	char	*str;
	char	*file;
	int		fd;

	i = 0;
	fd = open("map/map.cub", O_RDWR);
	init_list(info);
	str = skip_line(fd);
	file = NULL;
	info->bloc = NULL;
	while (str)
	{
		file = ft_strjoin(file, str);
		if(info->number_of_line >= 6)
			break;
		if (ft_strlen(str) > 1)
			info->number_of_line++;
		free(str);
		str = get_next_line(fd);
	}
	i = 0;
	if(ft_strlen(str) == 1)
	{
		str = skip_line(fd);
		i++;
	}
	if(i == 0)
		exit(1);
	info->bloc = ft_substr(file,0,ft_strlen(file));
	(free(file), close(fd));
}

char	*reaplace(char *text, int number)
{
	char	*result;
	int		resultIndex;
	int i;
	int j;

	result = malloc(ft_strlen(text) * number + 1);
	resultIndex = 0;
	i = 0;
	while (i < (int)ft_strlen(text))
	{
		if (text[i] == '\t')
		{
			j = 0;
			while (j < number)
			{
				result[resultIndex++] = ' ';
				j++;
			}
		}
		else
			result[resultIndex++] = text[i];
		i++;
	}
	result[resultIndex] = '\0';
	if (text)
	{
		free(text);
		text = NULL;
	}
	text = ft_strjoin(text,result);
	free(result);
	return text;
}

int	ft_strlen_2d(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

void	check_line(char **tab)
{
	int	i;

	i = ft_strlen_2d(tab);
	printf("%d\n", i);
	if (i != 1)
	{
		free_2d(tab);
		printf("1:ERROR\n");
		exit(0);
	}
}

void	check_direction(t_bloc *data_of_texture)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strlen(data_of_texture[i].val_1) > 2)
		{
			printf("2:ERROR\n");
			exit(0);
		}
		else
		{
			if (i < 5 && !ft_strncmp(data_of_texture[i].val_1, data_of_texture[i
					+ 1].val_1, 2))
			{
				printf("3:ERROR\n");
				exit(0);
			}
		}
		i++;
	}
}

void	type_of_bloc(t_bloc *lines)
{
	int	i;

	i = 0;
	lines->bloc_size_texteur = 0;
	lines->bloc_size_rgb = 0;
	while (i < 6)
	{
		if (ft_strlen(lines[i].val_1) == 2)
		{
			lines[i].type = PATH;
			lines->bloc_size_texteur++;
		}
		else if (ft_strlen(lines[i].val_1) == 1)
		{
			lines[i].type = RGB;
			lines->bloc_size_rgb++;
		}
		else
			lines[i].type = 0;
		i++;
	}
}

void	ft_fill_info(t_bloc *line, t_general *info_bloc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	info_bloc->info_texteur = malloc(sizeof(t_texteur)
			* line->bloc_size_texteur);
	info_bloc->info_rgb = malloc(sizeof(t_rgb_info) * line->bloc_size_rgb);
	while (i < 6)
	{
		if (line[i].type == PATH && j < line->bloc_size_texteur)
		{
			info_bloc->info_texteur[j].direction = ft_strdup(line[i].val_1);
			info_bloc->info_texteur[j].path = ft_strdup(line[i].val_2);
			free(line[i].val_2);
			free(line[i].val_1);
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (i < 6)
	{
		if (line[i].type == RGB && j < line->bloc_size_rgb)
		{
			info_bloc->info_rgb[j].type_color = ft_strdup(line[i].val_1);
			info_bloc->info_rgb[j].rgb_value = ft_strdup(line[i].val_2);
			free(line[i].val_2);
			free(line[i].val_1);
			j++;
		}
		i++;
	}
	//free(line);
}

void	ft_bloc(t_general *data, t_bloc *data_of_texture)
{
	int		i;
	char	**textures;
	char	**info;

	if (data->number_of_line != 6)
		(free(data->bloc), printf("4:ERROR\n"), exit(0));
	textures = ft_split(data->bloc, '\n');
	i = 0;
	while (i < data->number_of_line)
	{
		if (textures[i] && ft_strchr(textures[i], '\t'))
			textures[i] = reaplace(textures[i], 4);
		info = ft_split_pos(textures[i], ' ',1);
		data_of_texture[i].val_1 = ft_strdup(info[0]);
		data_of_texture[i].val_2 = ft_strdup(info[1]);
		printf("%s\n",info[0]);
		free_2d(info);
		i++;
	}
	check_direction(data_of_texture);
	type_of_bloc(data_of_texture);
	ft_fill_info(data_of_texture, data);
	free_2d(textures);
}

int	ft_block_texteurs(t_texteur *bloc_1)
{
	if (bloc_1->direction && (!ft_strncmp(bloc_1->direction, "NO", 2)
			|| !ft_strncmp(bloc_1->direction, "SO", 2)
			|| !ft_strncmp(bloc_1->direction, "WE", 2)
			|| !ft_strncmp(bloc_1->direction, "EA", 2)))
		return (0);
	else
		return (1);
}

int	ft_block_rgb(t_rgb_info *bloc_2)
{
	if (bloc_2->type_color && (!ft_strncmp(bloc_2->type_color, "C", 2)
			|| !ft_strncmp(bloc_2->type_color, "F", 2)))
		return (0);
	else
		return (1);
}

void	ft_parssing(void)
{
	t_general	*info;
	t_bloc		*data;
	char	**valid_path;
	static int	cont;
	int			i;

	info = malloc(sizeof(t_general));
	data = malloc(sizeof(t_bloc) * 6);
	read_lines_texter(info);
	ft_bloc(info, data);
	i = 0;
	while (i < data->bloc_size_texteur)
	{
		if (ft_block_texteurs(&info->info_texteur[i]) == 0)
			cont++;
		valid_path = ft_split(info->info_texteur[i].path,' ');
		check_line(valid_path);
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

	//clear_all(info, data->bloc_size_texteur, data->bloc_size_rgb);
}
