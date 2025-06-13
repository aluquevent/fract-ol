#include "fractol.h"
#include "mlx.h"

static void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iterations_def = 200;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 1;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, 02, 0, key_handler, fractal);
	mlx_hook(fractal->mlx_window, 04, 0, mouse_handler, fractal);
	mlx_hook(fractal->mlx_window, 17, 0, close_handler, fractal);
	mlx_hook(fractal->mlx_window, 06, 0, julia_track, fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (NULL == fractal->mlx_connection)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection,
									  WIDTH,
									  HEIGHT,
									  fractal->name);
	if (NULL == fractal->mlx_window)
	{
		//add mlx_destroy_display
		free(fractal->mlx_connection);
		malloc_error();
	}
	fractal->img.img = mlx_new_image(fractal->mlx_connection,
								   WIDTH, HEIGHT);
	if (NULL == fractal->img.img)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		//Add mlx_destroy_display
		free(fractal->mlx_connection);
		malloc_error();
	}
	fractal->img.addr = mlx_get_data_addr(fractal->img.img,
									   &fractal->img.bpp,
									   &fractal->img.line_length,
									   &fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}


