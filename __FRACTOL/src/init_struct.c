/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_struct.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:45:02 by jdobos        #+#    #+#                 */
/*   Updated: 2024/05/13 18:18:16 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

void	init_basic_struct(t_fractal *f)
{
	f->draw = true;
	f->offset_x = -0.8;
	if (f->set == julia)
		f->offset_x = 0.0;
	f->offset_y = 0.0;
	f->zoom = 1.0;
	f->ratio = (double)f->mlx->height / (double)f->mlx->width;
	f->iterations = 82;
	f->iterations_j = 2;
	f->inp = 1.0;
	f->lock_j = true;
}

void	init_split_struct(t_fractal *f)
{
	f->draw = true;
	f->draw_j = true;
	f->offset_x = -0.8;
	f->offset_y = 0.0;
	f->offset_x_j = 0.0;
	f->offset_y_j = 0.0;
	f->zoom = 1.0;
	f->zoom_j = 1.0;
	f->ratio = 1;
	f->iterations = 92;
	f->iterations_j = 92;
	f->inp = 1.0;
	f->lock_j = false;
}

void	init_null(t_fractal *f)
{
	f->mlx = NULL;
	f->img = NULL;
	f->img_j = NULL;
	f->palette_m = NULL;
	f->palette_j = NULL;
}

void	init_color(t_fractal *f)
{
	f->color_inf = BLACK;
	f->c_inf_m = BLACK;
	f->c_inf_n = BLACK;
	f->c_low = hex_to_rgba(BLACK);
	f->c_high = hex_to_rgba(WHITE);
	f->c_a = hex_to_rgba(BLACK);
	f->c_b = hex_to_rgba(ORANGE);
	f->c_c = hex_to_rgba(C_B);
	f->c_d = hex_to_rgba(C_M);
	f->palette = multi;
	f->retina_mode = false;
	f->i_multi = 0;
}
