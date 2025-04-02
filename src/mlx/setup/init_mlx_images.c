#include <stdlib.h>
#include <miniRT.h>
#include <RTmlx.h>
#include <render.h>
#include <miniRT.h>
#include <threadsRT.h>

bool	img_multithreaded(t_rt *rt)
{
	rt->thread.img = mlx_new_image(rt->win->mlx, (int32_t)rt->win->window_wdth, (int32_t)rt->win->window_hght);
	if (rt->thread.img == NULL)
	{
		return (false);
	}
	rt->win->id = mlx_image_to_window(rt->win->mlx, rt->thread.img, 0, 0);
	if (rt->win->id == -1)
	{
		return (mlx_delete_image(rt->win->mlx, rt->thread.img), false);
	}
	rt->thread.pixels_mlx = (uint8_t *)rt->thread.img->pixels;
	rt->thread.pixels_own = (uint8_t *)malloc(sizeof(uint8_t) * (rt->win->window_wdth * rt->win->window_hght * 4));
	if (rt->thread.pixels_own == NULL)
		return (mlx_delete_image(rt->win->mlx, rt->thread.img), false);
	rt->thread.pixels = rt->thread.pixels_own;
	return (true);
}
