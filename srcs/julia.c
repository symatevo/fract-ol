#include "../includes/fractol.h"

void	julia(int width, int height, t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->mlx_win);
	double		t;
	int			isinside;
	int			red, green, blue;
	int			x, y;
	double		iteration;
	int			color;
	t_complex	z;

	color = 0;
	isinside = 0;
	vars->prop.re = (vars->max.re - vars->min.re) / (width - 1);
	vars->prop.im = (vars->max.im - vars->min.im) / (height - 1);
	y = 0;
	while (y < height)
	{
		vars->real.im = vars->max.im - y * vars->prop.im;
		x = 0;
		while (x < width)
		{
			vars->real.re = vars->min.re + x * vars->prop.re;
			z = init_complex(vars->real.re, vars->real.im);
			iteration = 0;
			isinside = 1;
			while ((pow(z.re, 2.0) + pow(z.im, 2.0) <= 4) && iteration < vars->max_iteration)
			{
				z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + vars->k.re, 2.0 * z.re * z.im + vars->k.im);
				iteration++;
				if ((pow(z.re, 2.0) + pow(z.im, 2.0) > 4))
				{
					isinside = 0;
					break;
				}
			}
			t = (double)iteration / (double)vars->max_iteration;
			red = (int)(9 * (1 - t) * pow(t, 3) * 255);
			green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
			blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
			color = create_trgb(0, red, green, blue);
			if(isinside)
				mlx_pixel_put(vars->img, vars->mlx_win, x, y, 0x00ffff);
			else
				mlx_pixel_put(vars->img, vars->mlx_win, x, y, color);
			x++;
		}
		y++;
	}
}

int julia_motion(int x, int y, t_vars *vars)
{
    vars->k = init_complex(
        4 * ((double)x / 1920 - 0.5),
        4 * ((double)(1080 - y) / 1080 - 0.5));
    julia(1920, 1080, vars);
    return (0);
}
