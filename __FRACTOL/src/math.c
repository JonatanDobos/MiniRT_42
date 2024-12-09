/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:45:19 by jdobos        #+#    #+#                 */
/*   Updated: 2024/05/13 16:45:21 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

double	ft_scale_x(t_fractal *f, double val)
{
	const double	max_x = (X_MAX * f->zoom) + f->offset_x;
	const double	min_x = (X_MIN * f->zoom) + f->offset_x;

	return ((max_x - min_x) * val / f->mlx->width + min_x);
}

double	ft_scale_y(t_fractal *f, double val)
{
	const double	max_y = ((Y_MAX * f->zoom) + f->offset_y) * f->ratio;
	const double	min_y = ((Y_MIN * f->zoom) + f->offset_y) * f->ratio;

	return ((max_y - min_y) * val / f->mlx->height + min_y);
}

void	ft_fract_math(t_fractal *f, t_complex c, t_complex z)
{
	size_t		i;
	double		real_tmp;

	if ((c.x * c.x) + (c.y * c.y) < 0.0625 && f->set == mandel)
		return (mlx_put_pixel(f->img, f->x, f->y, f->color_inf));
	i = 0;
	while (i < f->iterations && (z.x * z.x) + (z.y * z.y) <= 4)
	{
		real_tmp = (z.x * z.x - z.y * z.y) + c.x;
		z.y = (2 * z.x * z.y) + c.y;
		z.x = real_tmp;
		i++;
	}
	if (i < f->iterations)
		return (mlx_put_pixel(f->img, f->x, f->y, \
				f->palette_m[i]));
	return (mlx_put_pixel(f->img, f->x, f->y, f->color_inf));
}

// split
void	ft_fract_math_jul(t_fractal *f, t_complex c, t_complex z)
{
	size_t		i;
	double		real_tmp;

	i = 0;
	while (i < f->iterations_j && (z.x * z.x) + (z.y * z.y) <= 4)
	{
		real_tmp = (z.x * z.x - z.y * z.y) + c.x;
		z.y = (2 * z.x * z.y) + c.y;
		z.x = real_tmp;
		i++;
	}
	if (i < f->iterations_j)
		return (mlx_put_pixel(f->img_j, f->x, f->y, \
				f->palette_j[i]));
	return (mlx_put_pixel(f->img_j, f->x, f->y, f->color_inf));
}
