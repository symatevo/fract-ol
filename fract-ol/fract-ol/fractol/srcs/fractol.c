/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: symatevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:55:58 by symatevo          #+#    #+#             */
/*   Updated: 2021/07/27 16:38:29 by symatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

t_complex init_complex(double re, double im)
{
	t_complex complex;	

	complex.re = re;
    	complex.im = im;
	return (complex);
}

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

char	ft_parser_forlow(unsigned int tmp, char str)
{
	if (tmp == 10)
		str = 'a';
	else if (tmp == 11)
		str = 'b';
	else if (tmp == 12)
		str = 'c';
	else if (tmp == 13)
		str = 'd';
	else if (tmp == 14)
		str = 'e';
	else
		str = 'f';
	return (str);
}

char	*convert_hex(unsigned int n, char *str, int size)
{
	unsigned int	tmp;
	char			*ptr;

	tmp = n;
	ptr = str;
	while (size > 0)
	{
		tmp = n % 16;
		n = n / 16;
		if (tmp < 10)
			*str = tmp + '0';
		else if (tmp > 9 && tmp < 16)
			*str = ft_parser_forlow(tmp, *str);
		str++;
		size--;
	}
	return (ptr);
}

/*char	*make_hex(unsigned int n)
{
	char			*str;
	unsigned int	tmp;
	int				size;

	tmp = n;
	size = 0;
	while (tmp > 0)
	{
		tmp = tmp / 16;
		size++;
	}
	str = calloc(sizeof(char), (size + 1));
	str = convert_hex(n, str, size);
	if (n == 0)
		*str = '0';
	str = ft_strrev_bonus(str);
	return (str);
}

int		*ft_rgb(int r, int g, int b)
char *str_1;
	str_1 = make_hex(r);
	char *str_2;
	str_2 = make_hex(g);
	char *str_3;
	str_3 = make_hex(b);
	int number;
	number = 0;
	number = x;
	number = number * 10 + str_1[0] - '0';
	number = number * 10 + str_1[1] - '0';
	number[4] = str_2[0] - '0';
	number[5] = str_2[1] - '0';
	number[6] = str_3[0] - '0';
	number[7] = str_3[1] - '0';
	return(number);
}	*/

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	julia(int WIDTH, int HEIGHT, void *img, void *mlx_win, t_complex k)
{
	double		t;
	int		isinside = 0;
	int		red, green, blue;
	t_min		min;
	t_max		max;
	t_proportion	prop;
	t_real		real;
	t_complex	z;
	int		x, y;
	double		iteration, max_iteration;
	int color = 0;

	k = init_complex(-0.4, 0.6);
	min.re = -2.0;
	max.re = 2.0;
	min.im = -2.0;
	max.im = 2.0 * HEIGHT / WIDTH;;
	prop.re = (max.re - min.re) / (WIDTH - 1);
	prop.im = (max.im - min.im) / (HEIGHT - 1);
	max_iteration = 100;
	y = 0;
	while (y < HEIGHT)
	{
		real.im = max.im - y * prop.im;
		//printf("%f", real.im);
		x = 0;
		while (x < WIDTH)
		{
			real.re = min.re + x * prop.re;
			z = init_complex(real.re, real.im);
			iteration = 0;
			isinside = 1;
			while ((pow(z.re, 2.0) + pow(z.im, 2.0) <= 4) && iteration < max_iteration)
			{
				//write(1, "s", 1);
				 z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + k.re, 2.0 * z.re * z.im + k.im);
				iteration++;
				if ((pow(z.re, 2.0) + pow(z.im, 2.0) > 4))
				{
					isinside = 0;
					break;
				}
			}
			t = (double)iteration / (double)max_iteration;
			red = (int)(9 * (1 - t) * pow(t, 3) * 255);
			green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
			blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
			color = create_trgb(0, red, green, blue);
			if(isinside)
				mlx_pixel_put(img, mlx_win, x, y, 0x00ffff);
			else
				mlx_pixel_put(img, mlx_win, x, y, color);
			x++;
		}
		y++;
	}
}

int julia_motion(int x, int y, t_complex k, int WIDTH, int HEIGHT, void *img, void *mlx_win)
{
    k = init_complex(
        4 * ((double)x / WIDTH - 0.5),
        4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
    julia(WIDTH, HEIGHT, img, mlx_win, k);
    return (0);
}

void	mandelbrot(int WIDTH, int HEIGHT, void *img, void *mlx_win)
{
	//write(1, "hasav", 7);
	double		t;
	int		isinside = 0;
	int		red, green, blue;
	t_min		min;
	t_max		max;
	t_proportion	prop;
	t_real		real;
	t_complex	z;
	int		x, y;
	double		iteration, max_iteration;
	int color = 0;

	min.re = -2.0;
	max.re = 2.0;
	min.im = -2.0;
	max.im = 2.0 * HEIGHT / WIDTH;;
	prop.re = (max.re - min.re) / (WIDTH - 1);
	prop.im = (max.im - min.im) / (HEIGHT - 1);
	max_iteration = 100;
	y = 0;
	while (y < HEIGHT)
	{
		real.im = max.im - y * prop.im;
		//printf("%f", real.im);
		x = 0;
		while (x < WIDTH)
		{
			real.re = min.re + x * prop.re;
			z = init_complex(real.re, real.im);
			iteration = 0;
			isinside = 1;
			while ((pow(z.re, 2.0) + pow(z.im, 2.0) <= 4) && iteration < max_iteration)
			{
				//write(1, "s", 1);
				z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + real.re,2.0 * z.re * z.im + real.im);
				iteration++;
				if ((pow(z.re, 2.0) + pow(z.im, 2.0) > 4))
				{
					isinside = 0;
					break;
				}
			}
			t = (double)iteration / (double)max_iteration;
			red = (int)(9 * (1 - t) * pow(t, 3) * 255);
			green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
			blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
			color = create_trgb(0, red, green, blue);
			if(isinside)
				mlx_pixel_put(img, mlx_win, x, y, 0x00ffff);
			else
				mlx_pixel_put(img, mlx_win, x, y, color);
			x++;
		}
		y++;
	}
}	

int main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;
	int x, y;
	x = 0;
	y = 0;
	t_complex k;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	if (argc == 2) // 1920 1080 hly vor erku heto kpoxes erku seteri parametreri hamar
	{
		if (!ft_strncmp(argv[1], "mandelbrot", 11))
			mandelbrot(1920, 1080, img.img, vars.win);
		if (!ft_strncmp(argv[1], "julia", 10))
		{
			k = init_complex(-0.4, 0.6);
			julia(1920, 1080, img.img, vars.win, k);
		}
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
	mlx_hook(vars.win, 6, 1L<<6, julia_motion, x, y, k)// 1920, 1080, img.img, vars.win);
	mlx_loop(vars.mlx);
	return (0);
}

