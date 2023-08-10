/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 03:38:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/10 03:53:14 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*reaplace(char *text, int number)
{
	char	*result;
	int		resultIndex;
	int		i;
	int		j;

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
	text = ft_strjoin(text, result);
	free(result);
	return (text);
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
