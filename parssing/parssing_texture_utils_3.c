/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_texture_utils_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:39:20 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/25 11:39:25 by rlarabi          ###   ########.fr       */
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
