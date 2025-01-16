#include "../include/minirt_param.h"

void	set_pixel(t_minirt *m, t_uin16 x, t_uin16 y, t_rgba color)
{
	const int	pixel_idx = (y * m->win.rndr_wdth + x) * 4;

	m->win.pixels[pixel_idx + 0] = color.r;
	m->win.pixels[pixel_idx + 1] = color.g;
	m->win.pixels[pixel_idx + 2] = color.b;
	m->win.pixels[pixel_idx + 3] = color.a;
}
