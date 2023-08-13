/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:31:15 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/13 03:38:25 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_general	*info;

	info = ft_parssing();
	info = ft_parssing_map(info);
	display_pixel(*info);

	// while(1){};
	// system("leaks cub3D");
}
