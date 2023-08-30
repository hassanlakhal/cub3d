/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <rlarabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:02:17 by rlarabi           #+#    #+#             */
/*   Updated: 2023/08/30 15:07:07 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_help_1(t_general *info, double *i, double *d)
{
	if (info->wall_hight > (double)HEIGHT)
	{
		(*i) = fabs((info->wall_hight / 2) - ((double)HEIGHT / 2));
		(*d) = info->wall_hight;
	}
	else
	{
		(*i) = 0;
		(*d) = HEIGHT;
	}
}

void	draw_help(t_general *info, t_data *texteur, int steps, double img_x)
{
	t_drawing	draw;

	draw.k = 0;
	draw.i = 0;
	draw.x_crement = (float)(int)(info->end->i - info->start->i) / (float)steps;
	draw.y_crement = (float)(int)(info->end->j - info->start->j) / (float)steps;
	draw.x = info->start->i;
	draw.y = info->start->j;
	draw_help_1(info, &draw.i, &draw.d);
	while (draw.i < draw.d)
	{
		my_mlx_pixel_put(info, (int)draw.x, (int)draw.y,
			my_mlx_get_pixel(texteur, (int)img_x, (int)draw.k));
		draw.k = draw.i / info->wall_hight * texteur->height;
		draw.x += draw.x_crement;
		draw.y += draw.y_crement;
		if (draw.x > WIDTH || draw.y > HEIGHT || draw.k > texteur->height)
			break ;
		draw.i++;
	}
	ft_draw_floor_sky(info, draw);
}

void	sub_draw_line(t_general *info, double endi, t_data *texteur)
{
	int		steps;
	double	img_x;

	if (abs((int)(info->end->i - info->start->i)) > abs((int)(info->end->j
				- info->start->j)))
		steps = abs((int)(info->end->i - info->start->i));
	else
		steps = abs((int)(info->end->j - info->start->j));
	img_x = ((int)texteur->width * (endi / 45 - floor(endi / 45)));
	draw_help(info, texteur, steps, img_x);
}

int	draw_line(t_general *info)
{
	int		i;
	double	temp;

	info->end = malloc(sizeof(t_coordinates));
	if (!info->end)
		return (0);
	info->start = malloc(sizeof(t_coordinates));
	if (!info->start)
		return (0);
	i = 0;
	temp = 60 / ((double)WIDTH);
	while (i < WIDTH)
	{
		calcule_of_wall(info, i, info->start);
		draw_texteur(info);
		info->bita_ray += temp;
		if (info->bita_ray >= 360)
			info->bita_ray = 0;
		free(info->h);
		free(info->v);
		i++;
	}
	free(info->end);
	free(info->start);
	return (0);
}

void	draw_texteur(t_general *info)
{
	if (info->h->lenght > info->v->lenght)
	{
		if (cos((info->bita_ray * PI) / 180) > 0)
			sub_draw_line(info, info->v->end.j, get_side_texteur(info, "EA"));
		else if (cos((info->bita_ray * PI) / 180) < 0)
			sub_draw_line(info, info->v->end.j, get_side_texteur(info, "WE"));
	}
	else
	{
		if (sin(((info->bita_ray * PI) / 180)) > 0)
			sub_draw_line(info, info->h->end.i, get_side_texteur(info, "SO"));
		else if (sin(((info->bita_ray * PI) / 180)) < 0)
			sub_draw_line(info, info->h->end.i, get_side_texteur(info, "NO"));
	}
}
