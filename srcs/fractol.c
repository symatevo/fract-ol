/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: symatevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:55:58 by symatevo          #+#    #+#             */
/*   Updated: 2021/07/31 18:18:26 by symatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_complex init_complex(double re, double im)
{
	t_complex complex;	

	complex.re = re;
    	complex.im = im;
	return (complex);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int				zoom(int button, int x, int y, t_vars *vars)
{
	t_complex	mouse;
	double		interpolation;
	double		zoom;

	if (button == 4 || button == 5)
	{
		mouse = init_complex(
			(double)x / (1920 / (vars->max.re - vars->min.re))
				+ vars->min.re,
			(double)y / (1080 / (vars->max.im - vars->min.im))
				* -1 + vars->max.im);
		if (button == 4)
			zoom = 0.80;
		else
			zoom = 1.20;
		interpolation = 1.0 / zoom;
		vars->min.re = interpolate(mouse.re, vars->min.re, interpolation);
		vars->min.im = interpolate(mouse.im, vars->min.im, interpolation);
		vars->max.re = interpolate(mouse.re, vars->max.re, interpolation);
		vars->max.im = interpolate(mouse.im, vars->max.im, interpolation);
		if (vars->fractol == 1)
			mandelbrot(1920, 1080, vars);
		if (vars->fractol == 2)
			julia(1920, 1080, vars);
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 2 && ((!ft_strncmp(argv[1], "mandelbrot", 11)) || (!ft_strncmp(argv[1], "julia", 6))))
	{
		t_vars vars;

		vars.mlx = mlx_init();
		vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
		vars.img = mlx_new_image(vars.mlx, 1920, 1080);
		vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length,
								&vars.endian);
		vars.min.re = -2.0;
		vars.max.re = 2.0;
		vars.min.im = -2.0;
		vars.max.im = 2.0 * 1080 / 1920;;
		vars.max_iteration = 100;
		if (!ft_strncmp(argv[1], "mandelbrot", 11))
		{
			vars.fractol = 1;
			mandelbrot(1920, 1080, &vars);
		}
		if (!ft_strncmp(argv[1], "julia", 6))
		{
			vars.fractol = 2;
			vars.k = init_complex(-0.4, 0.6);
			julia(1920, 1080, &vars);
		}
		if (!ft_strncmp(argv[1], "julia", 6))
			mlx_hook(vars.mlx_win, 6, 1L<<6, julia_motion, &vars);
		mlx_mouse_hook(vars.mlx_win, zoom, &vars);
		mlx_loop(vars.mlx);
	}
	else
	{
		 printf("= = = = = = = = = = = = =\n"
			"   C H O O S E   S E T   \n"
			"\n"
			"   - mandelbrot          \n"
			"   - julia               \n"
			"\n"
			"= = = = = = = = = = = = =\n");
	}
	return (0);
}

