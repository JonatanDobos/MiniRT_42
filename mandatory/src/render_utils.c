#include "../include/minirt_param.h"

void	set_pixel(t_window *w, t_uin16 x, t_uin16 y, t_vec4 color)
{
	const t_vec4	to_rgba = {255.0f, 255.0f, 255.0f, 255.0f};
	t_uint8			*pixels;

	color *= to_rgba;
	pixels = w->pixels + (y * w->rndr_wdth + x) * 4;
	pixels[0] = (t_uint8)color[R];
	pixels[1] = (t_uint8)color[G];
	pixels[2] = (t_uint8)color[B];
	pixels[3] = (t_uint8)color[A];
}

/**
 * @brief Broadcasts scalar value to all four indexes of the t_vec4.
 * @param scalar Value to broadcast to vector[X, Y, Z, W].
 * @return (t_vec4){scalar, scalar, scalar, scalar}
 */
t_vec4	bcast4(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, scalar});
}

/**
 * @brief Broadcasts scalar value to first three indexes of the t_vec4.
 * @param scalar Value to broadcast to vector[X, Y, Z].
 * @return (t_vec4){scalar, scalar, scalar, 1.0f}
 */
t_vec4	bcast3(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, 1.0f});
}
