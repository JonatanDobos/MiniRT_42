#include "../include/minirt_param.h"

// Creates an MLX window with image ready to be manipulated.
// t_window->wdth, hght and resize should be set beforehand!
// The rest will be filled in.
t_short	window_init(t_window *wdw, const char *name)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	wdw->inst = mlx_init(wdw->wdth, wdw->hght, name, wdw->resize);
	if (!wdw->inst)
		return (errn_set(perrmlx("mlx_init", mlx_errno)));
	wdw->img = mlx_new_image(wdw->inst, wdw->wdth, wdw->hght);
	if (!wdw->img)
	{
		mlx_terminate(wdw->inst);
		return (errn_set(perrmlx("mlx_new_image", mlx_errno)));
	}
	wdw->id = mlx_image_to_window(wdw->inst, wdw->img, 0, 0);
	if (wdw->id < 0)
	{
		mlx_terminate(wdw->inst);
		return (errn_set(perrmlx("mlx_image_to_window", mlx_errno)));
	}
	wdw->pixel_amount = wdw->wdth * wdw->hght;
	wdw->pixels = (t_uint8 *)wdw->img->pixels;
	return (SUCCESS);
}
