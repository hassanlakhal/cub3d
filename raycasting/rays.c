/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:07:48 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/25 13:11:55 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_casted_ray	*horizontal(t_general *info, double beta)
{
	t_casted_ray	*h;
	double			x_steps;
	double			y_steps;

	h = malloc(sizeof(t_casted_ray));
	step_rays(info, &x_steps, &y_steps, beta);
	if (beta == 0 || beta == 180)
	{
		h->lenght = INT_MAX;
		h->end.i = info->end->i;
		h->end.j = info->end->j;
		return (h);
	}
	while (break_wall(info, (int)info->end->i / 45, (int)info->end->j / 45))
	{
		info->end->i += x_steps;
		info->end->j += y_steps;
	}
	if (info->end->j > INT_MAX || info->end->i > INT_MAX
		|| info->end->j < INT_MIN || info->end->i < INT_MIN)
	{
		h->lenght = INT_MAX;
		return (h);
	}
	return (set_len(info, h), h);
}

t_casted_ray	*vertecal(t_general *info, double beta)
{
	t_casted_ray	*v;
	double			x_steps;
	double			y_steps;

	v = malloc(sizeof(t_casted_ray));
	step_rays_v(info, &x_steps, &y_steps, beta);
	if (beta == 90 || beta == 270)
	{
		v->lenght = INT_MAX;
		v->end.i = info->end->i;
		v->end.j = info->end->j;
		return (v);
	}
	while (break_wall(info, (int)info->end->i / 45, (int)info->end->j / 45))
	{
		info->end->i += x_steps;
		info->end->j += y_steps;
	}
	if (info->end->j > INT_MAX || info->end->i > INT_MAX
		|| info->end->j < INT_MIN || info->end->i < INT_MIN)
	{
		v->lenght = INT_MAX;
		return (v);
	}
	return (set_len(info, v), v);
}
