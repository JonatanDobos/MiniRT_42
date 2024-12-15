#include "../include/minirt_param.h"

/**
 * @brief Creates an MLX window with image ready to be manipulated.
 * @param win Pointer to t_window.
 * @param wdth Width of the window.
 * @param hght Height of the window.
 * @param name Name of the window.
 * @return Error code.
 * @note t_window->resize should be set beforehand!
 * @note The rest of t_window will be filled in.
 */
t_short	window_init(t_window *win, t_uint wdth, t_uint hght, const char *name)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	win->mlx = mlx_init(wdth, hght, name, win->resize);
	if (!win->mlx)
		return (errset(perrmlx("mlx_init", mlx_errno)));
	win->img = mlx_new_image(win->mlx, wdth, hght);
	if (!win->img)
	{
		mlx_terminate(win->mlx);
		return (errset(perrmlx("mlx_new_image", mlx_errno)));
	}
	win->id = mlx_image_to_window(win->mlx, win->img, 0, 0);
	if (win->id < 0)
	{
		mlx_terminate(win->mlx);
		return (errset(perrmlx("mlx_image_to_window", mlx_errno)));
	}
	win->ratio_w = (float)wdth / (float)hght;
	win->pixels = (t_uint8 *)win->img->pixels;
	if (win->rndr_hght == 0 && win->rndr_wdth == 0)
	{
		win->rndr_hght = hght;
		win->rndr_wdth = wdth;
	}
	return (SUCCESS);
}
