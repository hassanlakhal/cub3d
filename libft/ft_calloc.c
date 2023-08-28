/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:01:16 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/28 01:23:30 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size && (count > SIZE_MAX / size))
		return (NULL);
	p = (void *)malloc(size * count);
	if (p)
		ft_bzero(p, size * count);
	return (p);
}
