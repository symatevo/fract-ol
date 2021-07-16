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

void	mandelbrot(int HEIGHT, int WIDTH, void *img, void *mlx_win)
{
	int		color;
	int		t;
	int		red, green, blue;
	t_min		min;
	t_max		max;
	t_proportion	prop;
	t_real		real;
	t_complex	z;
	int		x, y;
	double		iteration, max_iteration;

	min.re = -2.0;
	max.re = 2.0;
	min.im = -2.0;
	max.im = min.im + (max.re - min.re) * HEIGHT / WIDTH;
	prop.re = (max.re - min.re) / (WIDTH - 1);
	prop.im = (max.im - min.im) / (HEIGHT - 1);

	max_iteration = 50;
	while (y < HEIGHT)
	{
		real.im = max.im - y * prop.im;
		x = 0;
		while (x < WIDTH)
		{
			real.re = min.re + x * prop.re;
			z = init_complex(real.re, real.im);
			iteration = 0;
			while ((pow(z.re, 2.0) + pow(z.im, 2.0) <= 4) && iteration < max_iteration)
			{
				z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + real.re,2.0 * z.re * z.im + real.im);
				iteration++;
			}
			t = (double)iteration / (double)max_iteration;
			red = (int)(9 * (1 - t) * pow(t, 3) * 255);
			green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
			blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
			color = red + green + blue;
			mlx_pixel_put(img, mlx_win, x, y, color);
			x++;
		}
		y++;
	}
}	

int main(int argc, char **argv)
{
	void *mlx;
	void *mlx_win;
	t_data	img;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	if (argc == 1) // hly vor mek heto kpoxes erku seteri parametreri hamar
	{
		if (!ft_strncmp(argv[1], "mandelbrot", 10))
			mandelbrot(1920, 1080, img.img, mlx_win);			
		if (!ft_strncmp(argv[1], "julia", 10))
			write(1, "julik", 6);
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
	mlx_loop(mlx);
	return (0);
}

