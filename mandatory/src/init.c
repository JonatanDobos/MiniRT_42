#include "../include/minirt_param.h"

void	init_struct_m(t_minirt *m)
{
	ft_bzero(m, sizeof(t_minirt));
	m->win.resize = true;
	m->win.ratio_w = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	m->win.rndr_hght = WIN_HEIGHT;
	m->win.rndr_wdth = WIN_WIDTH;
	// m->win.rndr_hght = RNDR_RES;
	// m->win.rndr_wdth = (t_uint)((float)RNDR_RES * m->win.ratio_w);
}
