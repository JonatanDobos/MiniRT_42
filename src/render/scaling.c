#include <scene.h>
#include <RTmlx.h>
#include <render.h>

bool	res_setscale(t_window *win, const float scale)
{
	win->res_ratio = scale;
	if (win->res_ratio < 1.0F)
		win->res_ratio = 1.0F;
	win->rndr_hght = (float)win->mlx->height / win->res_ratio;
	win->rndr_wdth = (float)win->mlx->width / win->res_ratio;
	return (true);
}
