/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:10:32 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/19 14:51:33 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int rgbToHex(int red, int green, int blue) {
    int hexInt = 0;
    
    hexInt = (red << 16) | (green << 8) | blue;
    return hexInt;
}