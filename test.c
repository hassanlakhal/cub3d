#include "cub3d.h"
#include <mlx.h>

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

int	main(void)
{
	t_vars	vars;
	double		x1;
	double		x2;
	double 	y2;
	double 	y1;
	float	slope;
	float	intercept;
	double		y;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 45 * 26, 45 * 7, "Line Drawing");
	x1 = 22 * 45;
	y1 = 4 * 45;
	x2 = x1 + 10.04;
	y2 = y1 + 20.05;
	printf("{x:%f}, {y:%f}\n",x2,y2);
	slope = (double)(y2 - y1) / (x2 - x1);
	intercept = y1 - slope * x1;
	for (double x = x1; x <= x2; x++)
	{
		y = (double)(slope * x + intercept);
		mlx_pixel_put(vars.mlx, vars.win, x, y, 0xFFFFFF);
			// Set pixel color (white in this case)
	}
	mlx_loop(vars.mlx);
}
