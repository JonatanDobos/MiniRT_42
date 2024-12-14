#include "../include/minirt_param.h"

// Creates an MLX window with image ready to be manipulated.
// t_window->wdth, hght and resize should be set beforehand!
// The rest will be filled in.
t_short	window_init(t_window *win, const char *name)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	win->mlx = mlx_init(win->wdth, win->hght, name, win->resize);
	if (!win->mlx)
		return (err_set(perrmlx("mlx_init", mlx_errno)));
	win->img = mlx_new_image(win->mlx, win->wdth, win->hght);
	if (!win->img)
	{
		mlx_terminate(win->mlx);
		return (err_set(perrmlx("mlx_new_image", mlx_errno)));
	}
	win->id = mlx_image_to_window(win->mlx, win->img, 0, 0);
	if (win->id < 0)
	{
		mlx_terminate(win->mlx);
		return (err_set(perrmlx("mlx_image_to_window", mlx_errno)));
	}
	win->pixel_amount = win->wdth * win->hght;
	win->pixels = (t_uint8 *)win->img->pixels;
	return (SUCCESS);
}
