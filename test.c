#include"cub3d.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int i;
	int j;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 190, 180, "Hello world!");
	img.img = mlx_new_image(mlx, 190, 180);
	çç
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(&img, 1 + j, 1 + i, 0x00FF0000);
			mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
			j++;
		}
		i++;
	}
	mlx_loop(mlx);
}
