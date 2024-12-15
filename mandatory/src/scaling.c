#include "../include/minirt_param.h"

float	render_scale_x(t_window *win, float val)
{
	const float	max_x = (float)win->rndr_wdth;
	const float	min_x = 0.0f;

	return ((max_x - min_x) * val / win->mlx->width + min_x);
}

float	render_scale_y(t_window *win, float val)
{
	const float	max_y = (float)win->rndr_hght;
	const float	min_y = 0.0f;

	return ((max_y - min_y) * val / win->mlx->height + min_y);
}
