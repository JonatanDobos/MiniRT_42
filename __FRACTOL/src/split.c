/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:45:28 by jdobos        #+#    #+#                 */
/*   Updated: 2024/05/13 16:50:11 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

void	ft_cursor_to_julia(void *param)
{
	t_fractal	*f;
	int32_t		x;
	int32_t		y;

	f = param;
	if (f->lock_j == true)
		return ;
	x = 0;
	y = 0;
	mlx_get_mouse_pos(f->mlx, &x, &y);
	if (x < 0 || y < 0 || x > M_WIDTH || y > M_HEIGHT)
		return ;
	f->julia_x = ft_scale_x(f, x * 2);
	f->julia_y = ft_scale_y(f, y);
	f->draw_j = true;
}

void	ft_split_scroll(double xdelta, double ydelta, void *param)
{
	t_fractal	*f;
	int32_t		x;
	int32_t		y;

	f = param;
	if (ft_cursor_check(f) == false || !ydelta || xdelta > 1)
		return ;
	mlx_get_mouse_pos(f->mlx, &x, &y);
	if (x < M_WIDTH)
	{
		if (ydelta > 0)
			f->zoom *= 0.95;
		if (ydelta < 0 && f->zoom < 100.0)
			f->zoom *= 1.05;
		f->draw = true;
	}
	else
	{
		if (ydelta > 0)
			f->zoom_j *= 0.95;
		if (ydelta < 0 && f->zoom_j < 100.0)
			f->zoom_j *= 1.05;
		f->draw_j = true;
	}
}

static void	move_man(t_fractal *f)
{
	if (mlx_is_key_down(f->mlx, MLX_KEY_UP))
	{
		f->offset_y += 0.05 * f->zoom;
		f->draw = true;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_DOWN))
	{
		f->offset_y -= 0.05 * f->zoom;
		f->draw = true;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_LEFT))
	{
		f->offset_x -= 0.05 * f->zoom;
		f->draw = true;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_RIGHT))
	{
		f->offset_x += 0.05 * f->zoom;
		f->draw = true;
	}
}

static void	move_jul(t_fractal *f)
{
	if (mlx_is_key_down(f->mlx, MLX_KEY_UP))
	{
		f->offset_y_j += 0.05 * f->zoom_j;
		f->draw_j = true;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_DOWN))
	{
		f->offset_y_j -= 0.05 * f->zoom_j;
		f->draw_j = true;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_LEFT))
	{
		f->offset_x_j -= 0.05 * f->zoom_j;
		f->draw_j = true;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_RIGHT))
	{
		f->offset_x_j += 0.05 * f->zoom_j;
		f->draw_j = true;
	}
}

void	split_move_hook(void *param)
{
	t_fractal	*f;
	int32_t		x;
	int32_t		y;

	f = param;
	if (!ft_cursor_check(f))
		return ;
	mlx_get_mouse_pos(f->mlx, &x, &y);
	if (x < M_WIDTH)
		move_man(f);
	else
		move_jul(f);
}
