/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/16 10:49:43 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void dispaly(void *mlx, void *mlx_win, t_general *info)
// {
// 	mlx_pixel_put();
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	//printf("a|h%d     y:%d|\n",data->height,y);
	//printf("b|h:%d   y:%d|\n",data->height,y);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	display_player(double x, double y, t_data *img, int color)
{
	x *= 45;
	y *= 45;
	
	my_mlx_pixel_put(img, (int)x, (int)y, color);
}

void	display_pxl(t_general *info, t_data *img, int j, int i)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->dimensions[1])
	{
		x = 0;
		while (x < info->dimensions[0])
		{
			if (info->valid_map[y][x] == '1')
				my_mlx_pixel_put(img, (x * 45) + j, (y * 45) + i, 0x00FF0000);
			if (info->valid_map[y][x] == '0')
				my_mlx_pixel_put(img, (x * 45) + j, (y * 45) + i, 0x00FFFFFF);
			if (ft_strchr("NEWS", info->valid_map[y][x]))
			{
				display_player(x, y, img, 0x4500FF);
				my_mlx_pixel_put(img, (x * 45) + j, (y * 45) + i, 0x00FFFFFF);
			}
			x++;
		}
		y++;
	}
}

void	ft_dislay(t_general *info, void *mlx, void *mlx_win)
{
	int		i;
	int		j;
	t_data	*img;

	img = malloc(sizeof(t_data));
	i = 1;
	// img->width = 45 * info->dimensions[0];
	// img->height = 45 * info->dimensions[1];
	img->img = mlx_new_image(mlx, 45 * info->dimensions[0], 45
			* info->dimensions[1]);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	info->info_img = img;
	// printf("add %p\n", img->img);
	while (i < 45)
	{
		j = 1;
		while (j < 45)
		{
			display_pxl(info, img, j, i);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
}

void	move_up(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	pos_x = info->info_player->pos_x + cos((info->alpha * PI) / 180) * 0.1;
	pos_y = info->info_player->pos_y + sin((info->alpha * PI) / 180) * 0.1;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		display_player(pos_x, pos_y, img, 0x00FF1FFF);
		display_player(info->info_player->pos_x, info->info_player->pos_y, img,
				0x00FFFFFF);
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, img->img, 0, 0);
}

void	move_down(t_general *info, t_data *img)
{
	double	pos_x;
	double	pos_y;

	pos_x = info->info_player->pos_x - cos((info->alpha * PI) / 180) * 0.1;
	pos_y = info->info_player->pos_y - sin((info->alpha * PI) / 180) * 0.1;
	if (info->valid_map[(int)pos_y][(int)pos_x] != '1')
	{
		display_player(pos_x, pos_y, img, 0x00FF1FFF);
		display_player(info->info_player->pos_x, info->info_player->pos_y, img,
				0x00FFFFFF);
		info->info_player->pos_x = pos_x;
		info->info_player->pos_y = pos_y;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, img->img, 0, 0);
}

void	rotate_right(t_general *info)
{
	info->alpha += 10;
	if (info->alpha >= 360)
		info->alpha = 0;
}

void	rotate_left(t_general *info)
{
	info->alpha -= 10;
	if (info->alpha < 0)
		info->alpha = 360;
}


void sub_draw_line(t_general *info,t_coordinates *start,t_coordinates *end)
{
	double		x1;
	double		x2;
	double 	y2;
	double 	y1;
	float	slope;
	float	intercept;
	double		y;
	// double	angle = info->alpha;

	x1 = start->i;
	y1 = start->j;
	x2 = end->i;
	y2 = end->j;
	slope = (double)(y2 - y1) / (x2 - x1);
	intercept = y1 - slope * x1;
	// if (x2 > info->dimensions[0] * 45)
	// {
	// 	printf("&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*\n");
	// 	exit(0);
	// }
	for (double x = x1; x < x2; x++)
	{
		y = (double)(slope * x + intercept);
		mlx_pixel_put(info->mlx, info->mlx_win, x, y, 0x000000);
			// Set pixel color (white in this case)
	}
}


double horizontal(t_general *info, int alpha)
{
	double next_y;
	t_coordinates start;
	t_coordinates end;
	next_y = 0; 
	if (sin(((info->alpha + alpha) * PI) * 180) > 0)
		next_y = (int)(info->info_player->pos_y*45) / 45  + 1;
	else if (sin(((info->alpha + alpha) * PI) * 180) < 0)
		next_y = (int)(info->info_player->pos_y*45) / 45;
	double dy = fabs(info->info_player->pos_y * 45 - next_y * 45);
	double dx  = fabs(dy / (tan(((info->alpha + alpha) * PI) / 180)));
	start.i = info->info_player->pos_x * 45;
	start.j = info->info_player->pos_y * 45;
	if (cos(((info->alpha + alpha) * PI) * 180) > 0 && sin(((info->alpha + alpha) * PI) * 180) < 0)
	{
		end.i = start.i + dx;
		end.j = fabs(start.j - dy);
	}
	else if (cos(((info->alpha + alpha) * PI) * 180) < 0 && sin(((info->alpha + alpha) * PI) * 180) < 0)
	{
		end.i = fabs(start.i - dx);
		end.j = fabs(start.j - dy);
	}
	else if (cos(((info->alpha + alpha) * PI) * 180) > 0 && sin(((info->alpha + alpha) * PI) * 180) > 0)
	{
		end.i = start.i + dx;
		end.j = start.j + dy;
	}
	else if (cos(((info->alpha + alpha) * PI) * 180) < 0 && sin(((info->alpha + alpha) * PI) * 180) > 0)
	{
		end.i = fabs(start.i - dx);
		end.j = start.j + dy;
	}	
	double l = sqrt(dx*dx + dy*dy);
	double x_steps;
	double y_steps;
	y_steps = 45;
	if(sin((((info->alpha + alpha) * PI) * 180) + alpha) < 0)
		y_steps = -45;
	x_steps = 45 / fabs(tan((((info->alpha + alpha) * PI) * 180) + alpha));
	if (cos((((info->alpha + alpha) * PI) * 180)+ alpha) < 0)
		x_steps *= -1;
	if(isinf(end.i))
		end.i = 0;
	while(1)
	{
		if (end.i < 0)
			end.i = 0;
		if(info->valid_map[(int)end.j/45 - 1][(int)end.i/45 - 1] == '1')
			break;
		end.i += x_steps;
		end.j += y_steps;
	}
	sub_draw_line(info ,&start,&end);
	return l;
}



double vertecal(t_general *info, int alpha)
{
	double next_x;
	t_coordinates start;
	t_coordinates end;
	next_x = 0; 
	if (cos(((info->alpha + alpha) * PI) * 180) > 0)
		next_x = (int)(info->info_player->pos_x*45) / 45  + 1;
	else if (cos(((info->alpha + alpha) * PI) * 180) < 0)
	next_x = (int)(info->info_player->pos_x*45) / 45;
	double dx = fabs(info->info_player->pos_x * 45 - next_x * 45);
	double dy = fabs(tan(((info->alpha + alpha) * PI) / 180) * dx);
	start.i = info->info_player->pos_x * 45;
	start.j = info->info_player->pos_y * 45;
	if (cos(((info->alpha + alpha) * PI) * 180) > 0 && sin(((info->alpha + alpha) * PI) * 180) < 0)
	{
		end.i = start.i + dx;
		end.j = fabs(start.j - dy);
	}
	if (cos(((info->alpha + alpha) * PI) * 180) < 0 && sin(((info->alpha + alpha) * PI) * 180) < 0)
	{
		end.i = fabs(start.i - dx);
		end.j = fabs(start.j - dy);
	}
	if (cos(((info->alpha + alpha) * PI) * 180) > 0 && sin(((info->alpha + alpha) * PI) * 180) > 0)
	{
		end.i = start.i + dx;
		end.j = start.j + dy;
	}
	if (cos(((info->alpha + alpha) * PI) * 180) < 0 && sin(((info->alpha + alpha) * PI) * 180) > 0)
	{
		end.i = fabs(start.j - dx);
		end.j = start.j + dy;
	}
	double l = sqrt(dx*dx + dy*dy);
	double x_steps;
	double y_steps;
	x_steps = 45;
	if(cos((((info->alpha + alpha) * PI) * 180) + alpha) < 0)
		x_steps = -45;
	y_steps = 45 * fabs(tan((((info->alpha + alpha) * PI) * 180) + alpha));
	if (sin((((info->alpha + alpha) * PI) * 180)+ alpha) < 0)
		y_steps *= -1;
	if(isinf(end.j))
		end.j = 0;
	while(1)
	{	
		if (end.j < 0)
			end.j = 0;
		//printf("y:%d\tx:%d\n",(int)end.j/45,(int)end.i/45);
		if(info->valid_map[(int)end.j/45][(int)end.i/45 - 1] == '1')
			break;
		end.i += x_steps;
		end.j += y_steps;
	}
	sub_draw_line(info ,&start,&end);
//	sub_draw_line(info , -30, l);
	return l;
}

int draw_line(t_general *info)
{
	double lv;
	double lh;
	lv = vertecal(info , 30);
	lh = horizontal(info , -30);

	// printf("V : %f\tH : %f\n", lv, lh);
	return 0;
}


int	key_hook(int key, t_general *info)
{
	// printf("%d\n",key);
	if (key == 65307)
		exit(0);
	else if (key == 65362 || key == 13)
		move_up(info, info->info_img);
	else if (key == 65364)
		move_down(info, info->info_img);
	else if (key == 65361)
		rotate_left(info);
	else if (key == 65363)
		rotate_right(info);
	return (0);
}

void	display_pixel(t_general info)
{
	// void	*mlx;
	// void	*mlx_win;
	info.alpha = 0;
	info.mlx = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx, 45 * info.dimensions[0], 45
			* info.dimensions[1], "cub3d");
	ft_dislay(&info, info.mlx, info.mlx_win);
	mlx_hook(info.mlx_win,2,3, key_hook, &info);
	mlx_loop_hook(info.mlx, draw_line, &info);
//	mlx_loop_hook(info.mlx, vertical, &info);
	mlx_loop(info.mlx);
}















// [Event "?"]
// [Site "?"]
// [Date "????.??.??"]
// [Round "?"]
// [White "?"]
// [Black "?"]
// [Result "0-1"]

// 1. e4 e5 {Right back atcha, buddy.} 2. Bc4 Nf6 3. d3 d5 4. exd5 Nxd5 5. Nf3 Bg4
// 6. a3 Bc5 7. Ba2 Nc6 8. O-O f5 9. Re1 Qd7 10. b4 Bd4 11. Qd2 Bxa1 12. b5 Bxf3
// 13. gxf3 Nd4 14. f4 Nf3+ {AHH $1 Get away from my king $1} 15. Kg2 Nxd2 16. Bxd2
// O-O-O 17. fxe5 b6 18. Kh1 Rde8 19. Rd1 Rxe5 20. f4 Re2 21. Bb3 Qd6 22. h4 Nxf4
// 23. Bc4 Nxd3 24. Bxd3 Qh2# {Aww $1 You played great, I loved your moves ^_^ Play
// again $2} 0-1