/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:31:15 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/24 14:10:02 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_general	*info;

	info = ft_parssing(ac, av);
	info = ft_parssing_map(info);
	display_pixel(*info);

	// while(1){};
	// system("leaks cub3D");
}
