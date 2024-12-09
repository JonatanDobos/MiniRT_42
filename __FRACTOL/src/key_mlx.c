/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_mlx.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:45:08 by jdobos        #+#    #+#                 */
/*   Updated: 2024/05/13 16:52:27 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

static void	ft_key_basic_non_retina(mlx_key_data_t keydata, t_fractal *f)
{
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		ft_set_switch(f);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		ft_reset_view(f);
	else if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		ft_window_size_set(f, 1);
	else if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		ft_window_size_set(f, 2);
	else if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		ft_window_size_set(f, 3);
	else if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		iteration_mod(f, 10);
	else if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		iteration_mod(f, -10);
	else if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
		ft_lock_j_switch(f);
}

void	ft_key_basic(mlx_key_data_t keydata, void *param)
{
	t_fractal	*f;

	f = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_all(f);
	else if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		ft_color_switch(f);
	else if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		palette_switch(f);
	else if (keydata.key == MLX_KEY_0 && keydata.action == MLX_PRESS)
		ft_retina_switch(f);
	else if (f->retina_mode == false)
		ft_key_basic_non_retina(keydata, f);
}

void	ft_key_split(mlx_key_data_t keydata, void *param)
{
	t_fractal	*f;

	f = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_all(f);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		ft_reset_view(f);
	else if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		iteration_mod(f, 10);
	else if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		iteration_mod(f, -10);
	else if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
		ft_lock_j_switch(f);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		ft_reset_view(f);
	else if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		ft_color_switch(f);
	else if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		palette_switch(f);
}

void	ft_cursor_to_julia_basic(void *param)
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
	if (f->set != julia || x < 0 || y < 0 || x > f->mlx->width || \
		y > f->mlx->height)
		return ;
	f->julia_x = ft_scale_x(f, x);
	f->julia_y = ft_scale_y(f, y);
	f->draw = true;
}
