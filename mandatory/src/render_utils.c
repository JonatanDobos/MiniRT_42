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

t_vec4	vcast(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, scalar});
}

t_vec4	ccast(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, scalar});
}
