/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   palette_init_j.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:45:22 by jdobos        #+#    #+#                 */
/*   Updated: 2024/06/11 12:57:16 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

void	init_color_palette_j(t_fractal *f, t_uint size)
{
	t_uint	i;
	double	t;

	f->palette_j = (t_uint *)malloc(sizeof(t_uint) * size);
	if (!f->palette_j)
		ft_error(f, "");
	i = 0;
	while (i < size)
	{
		t = (double)i / (double)size;
		if (f->palette == inverse)
			f->palette_j[i] = color_interpolate(f->c_high, f->c_low, t);
		else
			f->palette_j[i] = color_interpolate(f->c_low, f->c_high, t);
		i++;
	}
}

void	z_init_color_palette_j(t_fractal *f, t_uint size)
{
	t_uint	i;
	double	t;

	f->palette_j = (t_uint *)malloc(sizeof(t_uint) * size);
	if (!f->palette_j)
		ft_error(f, "");
	i = 0;
	while (i < size)
	{
		t = (double)i / (double)size;
		if (i % 2 == 0)
			f->palette_j[i] = color_interpolate(f->c_high, f->c_low, t);
		else
			f->palette_j[i] = color_interpolate(f->c_low, f->c_high, t);
		i++;
	}
}

void	multi_init_color_palette_j(t_fractal *f, t_uint size)
{
	t_uint			i;
	t_uint			start_i;
	t_uint			end_i;
	double			step;
	const t_color	arr[5] = {f->c_a, f->c_b, f->c_c, f->c_d, f->c_a};

	f->palette_j = (t_uint *)malloc(sizeof(t_uint) * size);
	if (!f->palette_j)
		ft_error(f, "");
	i = 0;
	step = (double)(size - 1) / 3;
	while (i < size)
	{
		start_i = i / step;
		end_i = start_i + 1;
		f->palette_j[i] = color_interpolate(arr[start_i], arr[end_i], \
			(double)(i - start_i * step) / step);
		i++;
	}
}
