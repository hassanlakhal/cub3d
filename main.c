/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:31:15 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/28 01:21:04 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	main(int ac, char **av)
{
	t_general	*info;

	info = ft_parssing(ac, av);
	info = ft_parssing_map(info);
	display_pixel(*info);
	clear_all(info);
	free(info);
	info = NULL;
	return (0);
}
