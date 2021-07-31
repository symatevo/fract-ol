#ifndef FRACTOL_H
#define FRACTOL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "./minilibx_opengl_20191021/mlx.h"

typedef	struct s_min
{
	double re;
	double im;
}	t_min;

typedef	struct s_max
{
	double re;
	double im;
}	t_max;

typedef struct s_proportion
{
	double re;
	double im;
}	t_proportion;

typedef struct s_real
{
	double re;
	double im;
}	t_real;

typedef struct s_complex
{
	double re;
	double im;
}	t_complex;

typedef struct s_vars
{
	void *mlx;
	void *mlx_win;
	void *img;
	void *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_min	min;
	t_max	max;
	t_proportion prop;
	t_real	real;
	t_complex k;
	int	fractol;
	double max_iteration;
}				t_vars;

void	mandelbrot(int width, int height, t_vars *vars);
void	julia(int width, int height, t_vars *vars);
int		julia_motion(int x, int y, t_vars *vars);
t_complex	init_complex(double re, double im);
int		create_trgb(int t, int r, int g, int b);

#endif
