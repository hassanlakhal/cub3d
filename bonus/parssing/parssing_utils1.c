/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 03:38:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/30 14:44:44 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*reaplace(char *text, int number, char c)
{
	char	*result;

	result = malloc(ft_strlen(text) * number + 1);
	if (!result)
		return (NULL);
	utils_reaplace(result, text, number, c);
	if (text)
	{
		free(text);
		text = NULL;
	}
	text = ft_strjoin(text, result);
	free(result);
	return (text);
}

void	check_dup(t_bloc *data_of_texture)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 6)
	{
		j = i + 1;
		while (j < 6)
		{
			if (!ft_strncmp(data_of_texture[i].val_1, data_of_texture[j].val_1,
					2))
			{
				printf("ERROR\nthere is a duplicate line\n");
				exit(1);
			}
			j++;
		}
		i++;
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
			printf("ERROR\nThere is an error in the format bloc one\n");
			exit(1);
		}
		else
			check_dup(data_of_texture);
		i++;
	}
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

void	check_line(char **tab, int a)
{
	int	i;

	i = ft_strlen_2d(tab);
	if ((i != 1 && a == PATH) || (i != 3 && a == RGB))
	{
		free_2d(tab);
		printf("ERROR\nproblem in PATH or RGB\n");
		exit(1);
	}
}
