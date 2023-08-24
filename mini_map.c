/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:23:08 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/08/24 04:51:33 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void ft_dispaly_palyer(t_general *info, int x, int y)
{
    int i;
    int j;
    i = 0;
    x = info->info_player->pos_x ;
    y = info->info_player->pos_y ;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            my_mlx_pixel_put(info,x + j,y + i,0xFF000FF);
            j++;
        }
        i++;
    }
       
}
void ft_display_black(t_general *info)
{
    int x;
    int y;
    int a = 0;
    int b;
    y = 0;
    while(a < 10)
    {
        b = 0;
        while(b < 10)
        {
            while (y < 100)
            {
                x = 0;
                while(x < 200)
                {
                    my_mlx_pixel_put(info, x + b, y + a,0xFFFFFF);
                    x++;       
                }
                y++;
            }
            b++;
        }
        a++;
    }
    
}

void ft_display_mini(t_general *info, int i,int j)
{
    double x;
    double y;
    (void)j;
    (void)i;
    int m,k;
    int s;
    y = info->info_player->pos_y - 0.7;
    k=0;
    while (y < info->info_player->pos_y + 0.7)
    {
        x = info->info_player->pos_x - 0.7;
        m = 0;
        s = info->info_player->pos_x;
        while (m < (s - (s % 20)))
        {
             if (((m) * 10) + j < 200 &&  k * 10 + i < 100 )
             {
                if (x < info->dimensions[0] && y < info->dimensions[1])
                {
                    if (info->valid_map[(int)y][(int)x] == '1')
                        my_mlx_pixel_put(info,(m * 10) + j,((k) * 10) + i,0x123545);
                    else
                        my_mlx_pixel_put(info,(m * 10) + j,((k) * 10) + i,0xFFFFFFF);
                }
                m++;
            }
            printf("[%f]----[%f]\n",x,y);
            // my_mlx_pixel_put(info,info->info_player->pos_x ,info->info_player->pos_y ,0xFF000FF);
            x++;
        } 
        k++;
        y++;
    }
    
}

void ft_mini_map(t_general *info, void *mlx, void *mlx_win)
{
    int i;
    int j;
    (void)mlx;
    (void)mlx_win;
    ft_display_black(info);
    
    i = 0;
    while (i < 10)
    {
        j = 0;
        while (j < 10)
        {
            ft_display_mini(info,i,j);
            j++;
        }
        i++;
    }
    // ft_dispaly_palyer(info, 0, 0);
    my_mlx_pixel_put(info, 100 ,50 ,0xFF000FF);

  //mlx_put_image_to_window(mlx, mlx_win, info->mini_map->img, 0, 0);
}