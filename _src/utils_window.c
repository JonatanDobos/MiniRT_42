#include "../_lib/minirt_param.h"

// USE NEW MLX VERSION!!

t_ushrt	window_init(t_window *wdw, const char *name)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	wdw->inst = mlx_init(wdw->wdth, wdw->hght, name, wdw->resize);
	if (!wdw->inst)
		return (FAILURE);
	wdw->img = mlx_new_image(wdw->inst, wdw->wdth, wdw->hght);
	if (!wdw->img || (mlx_image_to_window(wdw->inst, wdw->img, 0, 0) < 0))
		return (FAILURE);
	wdw->total_pixels = wdw->wdth * wdw->hght;
	return (SUCCESS);
}
