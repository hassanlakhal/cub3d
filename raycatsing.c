/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:21:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/14 03:37:46 by hlakhal-         ###   ########.fr       */
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

	//printf("a|h%d    y:%d|\n",data->height,y);
	//printf("b|h:%d   y:%d|\n",data->height,y);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	display_player(double x, double y, t_data *img, int color)
{
	int	i;
	int	j;

	i = 0;
	x *= 45;
	y *= 45;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
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
	if (info->alpha > 360)
		info->alpha = 0;
}

void	rotate_left(t_general *info)
{
	info->alpha -= 10;
	if (info->alpha < 0)
		info->alpha = 360;
}


void sub_draw_line(t_general *info , int beta)
{
	double		x1;
	double		x2;
	double		y2;
	double		y1;
	int			i = 0;
	double		lenght;
	x1 = (info->info_player->pos_x * 45);
	y1 = (info->info_player->pos_y * 45);
	x2 = x1 + cos(((info->alpha + beta)* PI) / 180) * 50;
	y2 = y1 + sin(((info->alpha + beta)* PI) / 180) * 50;
	lenght = get_lenght(info);
	while (i <= 200)
	{
		mlx_pixel_put(info->mlx, info->mlx_win, x1 , y1, 0x0000000);
		x1 += cos(((info->alpha + beta)* PI) / 180) ;
		y1 += sin(((info->alpha + beta)* PI) / 180) ;
		i++;
	}
}
int draw_line(t_general *info)
{
	sub_draw_line(info , 30);
	sub_draw_line(info , -30);

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