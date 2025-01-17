#include "../include/minirt_param.h"

void	set_pixel(t_minirt *m, t_uin16 x, t_uin16 y, t_rgba color)
{
	t_uint8		*pixels;

	pixels = m->win.pixels + (y * m->win.rndr_wdth + x) * 4;
	*(pixels++) = color.r;
	*(pixels++) = color.g;
	*(pixels++) = color.b;
	*(pixels++) = color.a;
}
