#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
//# include <X11/X.h>
# include <ApplicationServices/ApplicationServices.h>

# define WIDTH 800
# define HEIGHT 800
# define ERROR_MESSAGE "Error. Usage:\n\t./fractol mandelbrot\n"

#define BLK  0x000000  // Black
#define WHT  0xFFFFFF  // White
#define PNK  0xFF1493  // Neon Pink
#define LME  0xCCFF00  // Electric Lime
#define CYN  0x00FFFF  // Cyan
#define VIO  0x8B00FF  // Ultra Violet
#define ORG  0xFF4500  // Blood Orange
#define TEL  0x00FFCC

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_fractal
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	double	escape_value;
	int		iterations_def;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}	t_fractal;

typedef struct	s_complex
{
	double x;
	double y;
}	t_complex;

//Init
void		fractal_init(t_fractal *fractal);
void		malloc_error(void);
//Render
void		fractal_render(t_fractal *fractal);
//Events
int			key_handler(int keysys, t_fractal *fractal);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
int			julia_track(int x, int y, t_fractal *fractal);
//String utils
void		putstr_fd(char *str, int fd);

//Math utils
double	atodbl(char *s);
double		scale_map(double unscaled, double new_min, double new_max, double old_min, double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);
#endif // !
