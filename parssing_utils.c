/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 03:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/22 21:01:26 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_utils(char *str, int pos, int *delimiter_pos, char c)
{
	int		current_pos;
	int 	i;
	
	
	i = 0;
	current_pos = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == c)
		{
			current_pos++;
			if (current_pos == pos)
			{
				(*delimiter_pos) = i;
				break ;
			}
		}
		i++;
	}
}

char	**ft_split_pos(char *str, char c, int pos)
{
	char	**tab;
	int		delimiter_pos;
	
	ft_strlen(str);
	tab = (char **)malloc(3 * sizeof(char *));
	delimiter_pos = -1;
	ft_utils(str,pos,&delimiter_pos,c);
	if (delimiter_pos == -1)
	{
		printf("14:ERROR\n");
		exit(1);
	}
	tab[0] = ft_substr(str, 0, delimiter_pos);
	tab[1] = ft_substr(str, delimiter_pos, ft_strlen(str));
	tab[2] = NULL;
	return (tab);
}
