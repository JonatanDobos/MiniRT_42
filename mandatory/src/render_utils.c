#include "../include/minirt_param.h"

void	set_pixel(t_window *w, t_uin16 x, t_uin16 y, t_rgba color)
{
	t_uint8		*pixels;

	pixels = w->pixels + (y * w->rndr_wdth + x) * 4;
	pixels[0] = color[R];
	pixels[1] = color[G];
	pixels[2] = color[B];
	pixels[3] = color[A];
}

t_vec4	vcast(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, scalar});
}

t_rgba	ccast(float scalar)
{
	return ((t_rgba){scalar, scalar, scalar, scalar});
}
