/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_texture_utils_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:39:20 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/27 01:50:09 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	type_of_bloc(t_bloc *lines)
{
	int	i;
	int cont_1;
	int cont_2;

	i = 0;
	cont_1 = 0;
	cont_2 = 0;
	while (i < 6)
	{
		if (ft_strlen(lines[i].val_1) == 2)
		{
			lines[i].type = PATH;
			cont_1++;
		}
		else if (ft_strlen(lines[i].val_1) == 1)
		{
			lines[i].type = RGB;
			cont_2++;
		}
		else
			lines[i].type = 0;
		i++;
	}
	lines->bloc_size_texteur = cont_1;
	lines->bloc_size_rgb = cont_2;
}
