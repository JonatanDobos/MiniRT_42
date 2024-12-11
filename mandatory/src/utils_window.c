#include "../include/minirt_param.h"

// Creates an MLX window with image ready to be manipulated.
// t_window->wdth, hght and resize should be set beforehand!
// The rest will be filled in.
t_uint8	window_init(t_window *wdw, const char *name)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	wdw->inst = mlx_init(wdw->wdth, wdw->hght, name, wdw->resize);
	if (!wdw->inst)
		return (FAILURE);
	wdw->img = mlx_new_image(wdw->inst, wdw->wdth, wdw->hght);
	if (!wdw->img)
		return (mlx_terminate(wdw->inst), FAILURE);
	wdw->id = mlx_image_to_window(wdw->inst, wdw->img, 0, 0);
	if (wdw->id < 0)
		return (mlx_terminate(wdw->inst), FAILURE);
	wdw->total_pixels = wdw->wdth * wdw->hght;
	wdw->pixels = (t_uint8 *)wdw->img->pixels;
	return (SUCCESS);
}
