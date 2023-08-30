/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:10:32 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/28 00:53:25 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	rgb_to_hex(int red, int green, int blue)
{
	int	hexint;

	hexint = 0;
	hexint = (red << 16) | (green << 8) | blue;
	return (hexint);
}
