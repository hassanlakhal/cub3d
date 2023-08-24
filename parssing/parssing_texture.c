/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:00:03 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/24 14:27:41 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	ft_fill_info_1(t_bloc *line, t_general *info_bloc)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < 6)
	{
		if (line[i].type == PATH && j < line->bloc_size_texteur)
		{
			info_bloc->info_texteur[j].direction = ft_strdup(line[i].val_1);
			info_bloc->info_texteur[j].path = ft_strdup(line[i].val_2);
			(free(line[i].val_2), free(line[i].val_1));
			j++;
		}
		i++;
	}
}
void	ft_fill_info_2(t_bloc *line, t_general *info_bloc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 6)
	{
		if (line[i].type == RGB && j < line->bloc_size_rgb)
		{
			info_bloc->info_rgb[j].type_color = ft_strdup(line[i].val_1);
			info_bloc->info_rgb[j].rgb_value = ft_strdup(line[i].val_2);
			(free(line[i].val_2), free(line[i].val_1));
			j++;
		}
		i++;
	}
}

void	ft_fill_info(t_bloc *line, t_general *info_bloc)
{
	info_bloc->info_texteur = malloc(sizeof(t_texteur)
			* line->bloc_size_texteur);
	info_bloc->info_rgb = malloc(sizeof(t_rgb_info) * line->bloc_size_rgb);
	ft_fill_info_1(line, info_bloc);
	ft_fill_info_2(line, info_bloc);
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
			textures[i] = reaplace(textures[i], 4, '\t');
		info = ft_split_pos(textures[i], ' ', 1);
		data_of_texture[i].val_1 = ft_strdup(info[0]);
		data_of_texture[i].val_2 = ft_strdup(info[1]);
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

void	valid_format_1(char c, bool *intoken, int *digit)
{
	if (c >= '0' && c <= '9')
	{
		(*intoken) = true;
		(*digit)++;
	}
}

void	valid_format_2(int intoken, int *digit, int *token)
{
	if (intoken)
	{
		(*digit)++;
		(*token)++;
	}
}
bool	valid_format(const char *input)
{
	int		token;
	int		digit;
	bool	intoken;
	int		i;

	i = -1;
	token = 0;
	digit = 0;
	intoken = false;
	while (input[++i] != '\0')
	{
		if (input[i] == ',')
		{
			if (!intoken)
				return (false);
			intoken = false;
			token++;
		}
		else if (input[i] == ' ' || (input[i] >= '0' && input[i] <= '9'))
			valid_format_1(input[i], &intoken, &digit);
		else
			return (false);
	}
	valid_format_2(intoken, &digit, &token);
	return (token == 3 && digit >= 3);
}

void	cont_of_coma(char *rgb)
{
	int	i;
	int	cont;

	cont = 0;
	i = 0;
	while (rgb[i] && rgb[i] == 32)
		i++;
	while (rgb[i])
	{
		if (rgb[i] == ',')
			cont++;
		i++;
	}
	if (cont != 2)
	{
		printf("11:ERROR\n");
		exit(1);
	}
	else
	{
		if (!valid_format(rgb))
		{
			printf("12:ERROR\n");
			exit(0);
		}
	}
}

void	fill_rgb_val(char **rgb_val, t_general *info, int index)
{
	int	i;

	i = 0;
	while (rgb_val[i])
	{
		if (ft_strlen(rgb_val[i]) > 3 || ft_atoi(rgb_val[i]) > 255)
		{
			printf("15:ERROR\n");
			free_2d(rgb_val);
			exit(0);
		}
		i++;
	}
	info->info_rgb[index]._R = ft_atoi(rgb_val[0]);
	info->info_rgb[index]._G = ft_atoi(rgb_val[1]);
	info->info_rgb[index]._B = ft_atoi(rgb_val[2]);
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
		printf("7:ERROR\n");
		exit(0);
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
		printf("7:ERROR\n");
		exit(0);
	}
}
char *get_name_map(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Invalid Arguments\n");
		exit(1);
	}
	return ft_strdup(av[1]);
}
t_general	*ft_parssing(int ac, char **av)
{
	t_general	*info;
	t_bloc		*data;

	info = malloc(sizeof(t_general));
	data = malloc(sizeof(t_bloc) * 6);
	info->name_map = get_name_map(ac, av);
	read_lines_texter(info);
	ft_bloc(info, data);
	sub_parsing_1(info, data);
	sub_parsing_2(info, data);
	free(data);
	return (info);
	// clear_all(info, data->bloc_size_texteur, data->bloc_size_rgb);
}