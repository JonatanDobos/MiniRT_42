/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:45:14 by jdobos        #+#    #+#                 */
/*   Updated: 2024/05/13 16:45:15 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

bool	ft_cursor_check(t_fractal *f)
{
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(f->mlx, &x, &y);
	if (x < 0 || y < 0 || x > f->mlx->width || y > f->mlx->height)
		return (false);
	return (true);
}

void	ft_scroll(double xdelta, double ydelta, void *param)
{
	t_fractal	*f;

	f = param;
	if (ft_cursor_check(f) == false || !ydelta || xdelta > 1 || \
		f->retina_mode == true)
		return ;
	if (ydelta > 0)
	{
		f->zoom *= 0.95;
	}
	if (ydelta < 0 && f->zoom < 100.0)
	{
		f->zoom *= 1.05;
	}
	f->draw = true;
}

void	ft_reset_view(t_fractal *f)
{
	int32_t	x;
	int32_t	y;

	if (!ft_cursor_check(f))
		return ;
	mlx_get_mouse_pos(f->mlx, &x, &y);
	if (f->split == false || (f->split == true && x < M_WIDTH))
	{
		f->draw = true;
		f->offset_x = -0.8;
		if (f->set == julia)
			f->offset_x = 0.0;
		f->offset_y = 0.0;
		f->zoom = 1.0;
	}
	else
	{
		f->draw_j = true;
		f->zoom_j = 1.0;
		f->offset_x_j = 0.0;
		f->offset_y_j = 0.0;
	}
}

void	ft_set_switch(t_fractal *f)
{
	if (f->set == mandel)
	{
		mlx_set_window_title(f->mlx, "julia");
		f->set = julia;
		ft_reset_view(f);
		f->offset_x = 0.0;
	}
	else if (f->set == julia)
	{
		mlx_set_window_title(f->mlx, "mandelbrot");
		f->set = mandel;
		ft_reset_view(f);
	}
}

void	ft_lock_j_switch(t_fractal *f)
{
	if (f->lock_j == true)
		f->lock_j = false;
	else
		f->lock_j = true;
}
