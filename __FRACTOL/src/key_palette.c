/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_palette.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:45:11 by jdobos        #+#    #+#                 */
/*   Updated: 2024/05/13 18:24:42 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

// FIX LENGTH
void	ft_color_switch_multi(t_fractal *f)
{
	const t_uint	i[7] = {BLACK, BLACK, BLACK, C_F, C_E, WATER, BLACK};
	const t_uint	a[7] = {BLACK, C_I, C_G, C_D, C_H, C_L, BLACK};
	const t_uint	b[7] = {ORANGE, C_A, C_A, ORANGE, ORANGE, SHORE, BLACK};
	const t_uint	c[7] = {C_B, BLUE, C_J, WATER, C_C, C_C, ORANGE};
	const t_uint	d[7] = {C_M, C_K, C_F, C_F, C_E, WATER, C_M};

	f->i_multi++;
	if (f->i_multi == 7)
		f->i_multi = 0;
	f->c_inf_m = i[f->i_multi];
	f->c_a = hex_to_rgba(a[f->i_multi]);
	f->c_b = hex_to_rgba(b[f->i_multi]);
	f->c_c = hex_to_rgba(c[f->i_multi]);
	f->c_d = hex_to_rgba(d[f->i_multi]);
	re_init_palette(f, mandel);
	f->draw = true;
	if (f->split == true)
	{
		re_init_palette(f, julia);
		f->draw_j = true;
	}
}

void	ft_color_switch(t_fractal *f)
{
	const t_uint	arr_i[5] = {BLACK, WHITE, LAND, BLACK, WHITE};
	const t_uint	arr_h[5] = {WHITE, PINK, SHORE, ORANGE, WHITE};
	const t_uint	arr_l[5] = {BLACK, CYAN, WATER, WHITE, BLACK};
	static int		i = 0;

	if (f->palette == multi)
		return (ft_color_switch_multi(f));
	i++;
	if (i == 5)
		i = 0;
	f->c_inf_n = arr_i[i];
	f->c_high = hex_to_rgba(arr_h[i]);
	f->c_low = hex_to_rgba(arr_l[i]);
	re_init_palette(f, mandel);
	f->draw = true;
	if (f->split == true)
	{
		re_init_palette(f, julia);
		f->draw_j = true;
	}
}

void	palette_switch(t_fractal *f)
{
	if (f->palette == normal)
		f->palette = inverse;
	else if (f->palette == inverse)
		f->palette = zebra;
	else if (f->palette == zebra)
		f->palette = multi;
	else if (f->palette == multi)
		f->palette = normal;
	re_init_palette(f, mandel);
	f->draw = true;
	if (f->split == true)
	{
		re_init_palette(f, julia);
		f->draw_j = true;
	}
}

void	ft_retina_switch(t_fractal *f)
{
	static int	tmp_iterations = 0;

	if (f->retina_mode)
	{
		f->iterations = tmp_iterations;
		re_init_palette(f, mandel);
		f->retina_mode = false;
	}
	else
	{
		f->lock_j = true;
		f->retina_mode = true;
		tmp_iterations = f->iterations;
		f->iterations = RETINA_ITER;
		re_init_palette(f, mandel);
	}
	f->draw = true;
}

void	re_init_palette(t_fractal *f, short set)
{
	if (f->palette == multi)
		f->color_inf = f->c_inf_m;
	else
		f->color_inf = f->c_inf_n;
	if (set == mandel)
	{
		free(f->palette_m);
		if (f->palette == zebra)
			return (z_init_color_palette_m(f, f->iterations));
		if (f->palette == multi)
			return (multi_init_color_palette_m(f, f->iterations));
		init_color_palette_m(f, f->iterations);
		return ;
	}
	if (set == julia)
	{
		free(f->palette_j);
		if (f->palette == zebra)
			return (z_init_color_palette_j(f, f->iterations_j));
		if (f->palette == multi)
			return (multi_init_color_palette_j(f, f->iterations_j));
		init_color_palette_j(f, f->iterations_j);
		return ;
	}
}
