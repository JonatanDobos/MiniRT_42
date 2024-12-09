/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:44:59 by jdobos        #+#    #+#                 */
/*   Updated: 2024/05/13 16:48:19 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

void	ft_draw_mandel(t_fractal *f)
{
	t_complex	c;
	t_complex	z;

	f->draw = false;
	f->y = 0;
	z.x = 0.0;
	z.y = 0.0;
	while (f->y < f->mlx->height)
	{
		f->x = 0;
		while (f->x < f->mlx->width)
		{
			c.x = ft_scale_x(f, f->x);
			c.y = ft_scale_y(f, f->y);
			ft_fract_math(f, c, z);
			f->x++;
		}
		f->y++;
	}
}

void	ft_draw_julia(t_fractal *f)
{
	t_complex	c;
	t_complex	z;

	f->draw = false;
	f->y = 0;
	c.x = f->julia_x;
	c.y = f->julia_y;
	while (f->y < f->mlx->height)
	{
		f->x = 0;
		while (f->x < f->mlx->width)
		{
			z.x = ft_scale_x(f, f->x);
			z.y = ft_scale_y(f, f->y);
			ft_fract_math(f, c, z);
			f->x++;
		}
		f->y++;
	}
}

// split
void	ft_draw_mandel_split(t_fractal *f, t_complex z)
{
	t_complex		c;
	const double	max_x = (X_MAX * f->zoom) + f->offset_x;
	const double	min_x = (X_MIN * f->zoom) + f->offset_x;
	const double	max_y = (Y_MAX * f->zoom) + f->offset_y;
	const double	min_y = (Y_MIN * f->zoom) + f->offset_y;

	f->draw = false;
	f->y = 0;
	while (f->y < M_HEIGHT)
	{
		f->x = 0;
		while (f->x < M_WIDTH)
		{
			c.x = (max_x - min_x) * f->x / M_WIDTH + min_x;
			c.y = (max_y - min_y) * f->y / M_HEIGHT + min_y;
			ft_fract_math(f, c, z);
			f->x++;
		}
		f->y++;
	}
}

// split
void	ft_draw_julia_split(t_fractal *f, t_complex c)
{
	t_complex		z;
	const double	max_x = (X_MAX_J * f->zoom_j) + f->offset_x_j;
	const double	min_x = (X_MIN_J * f->zoom_j) + f->offset_x_j;
	const double	max_y = (Y_MAX_J * f->zoom_j) + f->offset_y_j;
	const double	min_y = (Y_MIN_J * f->zoom_j) + f->offset_y_j;

	f->draw_j = false;
	f->y = 0;
	while (f->y < J_HEIGHT)
	{
		f->x = 0;
		while (f->x < J_WIDTH)
		{
			z.x = (max_x - min_x) * f->x / J_WIDTH + min_x;
			z.y = (max_y - min_y) * f->y / J_HEIGHT + min_y;
			ft_fract_math_jul(f, c, z);
			f->x++;
		}
		f->y++;
	}
}

void	ft_image_resize(int32_t width, int32_t height, void *param)
{
	t_fractal	*f;

	f = param;
	if (f->retina_mode == true)
		ft_retina_switch(f);
	mlx_resize_image(f->img, width, height);
	f->ratio = (double)height / (double)width;
	f->draw = true;
}
