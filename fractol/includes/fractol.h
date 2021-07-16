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

#endif
