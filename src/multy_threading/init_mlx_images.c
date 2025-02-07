#include <stdlib.h>
#include <miniRT.h>
#include <RTmlx.h>
#include <render.h>

//	Static Functions
static bool	init_mlx(t_window *win);
static bool	img_to_window(t_window *win);
static bool	windows_logo(t_window *win);
static void	center_window(t_window *win);

bool	windows_setup_mlx(t_rt *rt)
{
	if (init_mlx(rt->win) == false || \
		img_to_window(rt->win) == false || \
		windows_logo(rt->win) == false)
		return (EXIT_FAILURE);
	center_window(rt->win);
	res_setscale(rt->win, RES_R_LOW);
	mlx_set_window_title(rt->win->mlx, "miniRT");
	init_hooks(rt);

	return (EXIT_SUCCESS);
}


static bool	img_to_window(t_window *win)
{
	// thread amount of img
	win->img = mlx_new_image(win->mlx, (int32_t)win->window_wdth, (int32_t)win->window_hght);
	if (win->img == NULL)
		return (false);
	win->id = mlx_image_to_window(win->mlx, win->img, 0, 0);
	if (win->id == -1)
		return (false);
	win->pixels = (uint8_t *)win->img->pixels;
	return (true);
}
