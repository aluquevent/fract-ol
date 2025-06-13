#include "fractol.h"

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = color;
}

static void	mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = (scale_map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (scale_map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
	mandel_vs_julia(&z, &c, fractal);
	while (i < fractal->iterations_def)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			color = scale_map(i, BLK, WHT, 0, fractal->iterations_def);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, &fractal->img, VIO);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while(++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
						 fractal->img.img,
						 0, 0);
}
