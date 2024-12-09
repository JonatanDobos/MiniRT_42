/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:44:17 by jdobos        #+#    #+#                 */
/*   Updated: 2024/06/10 14:28:48 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include "../libft/libft.h"
# include "MLX42/MLX42.h"

# define ERR_MESSAGE "Input ERROR! Correct input format:\n./fractol \
[mandelbrot/ julia/ split] [x, yi](option for julia)"
# define RETINA_ITER 1600

// NORMAL MODE

# define WIDTH_A 900
# define HEIGHT_A 600
# define WIDTH_B 600
# define HEIGHT_B 400
# define WIDTH_C 1200
# define HEIGHT_C 1200

// starting grid position
# define X_MAX 2.0
# define X_MIN -2.0
# define Y_MAX -2.0
# define Y_MIN 2.0

// SPLIT MODE

// window
# define S_WIDTH 2000
# define S_HEIGHT 1000

// mandelbrot
# define M_WIDTH 1000
# define M_HEIGHT 1000

// julia
# define J_WIDTH 1000
# define J_HEIGHT 1000

# define X_MAX_J 2.0
# define X_MIN_J -2.0
# define Y_MAX_J -2.0
# define Y_MIN_J 2.0

// COLOURS

# define BLACK	0x000000FF
# define WHITE	0xFFFFFFFF
# define SHORE	0xFFDD88FF
# define LAND	0x337711FF
# define WATER	0x3399FFFF
# define BLUE	0x4444DDFF
# define CYAN	0x00FFFF88
# define ORANGE	0xFC9A08FF
# define PINK	0xFC08C3BB

// C_A = BROWN
// C_B = GOLD
// C_C = CRIMSON
// C_D = BEIGE
// C_E = CORNSILK
// C_F = ANTIQUE_WHITE
// C_G = BLANCHED_ALMOND
// C_H = BISQUE
// C_I = WHEAT
// C_J = DARK_SLATE_BLUE
// C_K = PLUM
// C_L = LIGHT_SKY_BLUE
// C_M = LIGHT_STEEL_BLUE

# define C_A	0xA52A2AFF
# define C_B	0xFFD755FF
# define C_C	0xDC143CFF
# define C_D	0xF5F5DCFF
# define C_E	0xFFF8DCFF
# define C_F	0xFAEBD7FF
# define C_G	0xFFEBCDFF
# define C_H	0xFFE4C4FF
# define C_I	0xF5DEB3FF
# define C_J	0x040947FF
# define C_K	0xDDA0DDFF
# define C_L	0x87CEFAFF
# define C_M	0xB0C4DEFF

// ENUMERATIONS

enum	e_axis
{
	x_ax,
	y_ax
};

enum	e_sets
{
	mandel = 1,
	julia = 2
};

enum	e_palettes
{
	normal,
	zebra,
	inverse,
	multi
};

// STRUCTS

// complex point, x = real, y = imaginary
typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_color_char
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_color;

typedef struct s_color_double
{
	double	r;
	double	g;
	double	b;
	double	a;
}	t_color_d;

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

typedef struct s_fractal
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img_j;
	t_uint		*palette_m;
	t_uint		*palette_j;
	t_color		c_low;
	t_color		c_high;
	t_uint		color_inf;
	t_uint		c_inf_n;
	t_uint		c_inf_m;
	t_color		c_a;
	t_color		c_b;
	t_color		c_c;
	t_color		c_d;
	size_t		iterations;
	size_t		iterations_j;
	short		set;
	double		inp;
	double		zoom;
	double		zoom_j;
	double		ratio;
	double		offset_x;
	double		offset_y;
	double		offset_x_j;
	double		offset_y_j;
	bool		draw;
	bool		draw_j;
	bool		lock_j;
	int			x;
	int			y;
	double		julia_x;
	double		julia_y;
	bool		split;
	bool		retina_mode;
	short		palette;
	t_uint		i_multi;
}	t_fractal;

// FUNCTION PARAMETERS

void	ft_draw_mandel(t_fractal *f);
void	ft_draw_julia(t_fractal *f);
void	ft_draw_mandel_split(t_fractal *f, t_complex z);
void	ft_draw_julia_split(t_fractal *f, t_complex c);
void	ft_image_resize(int32_t width, int32_t height, void *param);

void	ft_key_basic(mlx_key_data_t keydata, void *param);
void	ft_key_split(mlx_key_data_t keydata, void *param);
void	ft_scroll(double xdelta, double ydelta, void *param);
void	ft_split_scroll(double xdelta, double ydelta, void *param);
void	split_move_hook(void *param);
bool	ft_cursor_check(t_fractal *f);
void	ft_reset_view(t_fractal *f);
void	ft_set_switch(t_fractal *f);
void	ft_lock_j_switch(t_fractal *f);

void	ft_color_switch_multi(t_fractal *f);
void	ft_color_switch(t_fractal *f);
void	palette_switch(t_fractal *f);
void	ft_retina_switch(t_fractal *f);

void	ft_fract_math(t_fractal *f, t_complex c, t_complex z);
void	ft_fract_math_jul(t_fractal *f, t_complex c, t_complex z);

double	ft_scale_x(t_fractal *f, double val);
double	ft_scale_y(t_fractal *f, double val);

t_uint	round_to_uint(double n);
t_uint	rgba_to_hex(t_color c);
t_color	hex_to_rgba(t_uint hex);
t_uint	color_interpolate(t_color c_l, t_color c_h, double t);
void	re_init_palette(t_fractal *f, short set);

void	init_color_palette_m(t_fractal *f, t_uint size);
void	init_color_palette_j(t_fractal *f, t_uint size);
void	z_init_color_palette_m(t_fractal *f, t_uint size);
void	z_init_color_palette_j(t_fractal *f, t_uint size);
void	multi_init_color_palette_m(t_fractal *f, t_uint size);
void	multi_init_color_palette_j(t_fractal *f, t_uint size);

void	ft_cursor_to_julia(void *param);
void	ft_cursor_to_julia_basic(void *param);

void	assign_hooks_basic(t_fractal *f);
void	assign_hooks_split(t_fractal *f);

int		num_check(t_fractal *f, char *arg, int i);
bool	arg_check(t_fractal *f, char *arg);
void	assign_jul_c(t_fractal *f, char *arg);

void	init_basic_struct(t_fractal *f);
void	init_split_struct(t_fractal *f);
void	init_null(t_fractal *f);
void	init_color(t_fractal *f);

void	iteration_mod(t_fractal *f, short mod);
void	ft_window_size_set(t_fractal *f, short size);
void	close_all(void *param);
void	ft_error(t_fractal *f, char *message);

#endif