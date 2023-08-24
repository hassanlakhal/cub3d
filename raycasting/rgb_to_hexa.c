/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:10:32 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/24 14:27:27 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	rgbToHex(int red, int green, int blue)
{
	int hexInt = 0;

	hexInt = (red << 16) | (green << 8) | blue;
	return (hexInt);
}