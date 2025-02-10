#include <stdlib.h>
#include <miniRT.h>
#include <RTmlx.h>
#include <render.h>
#include <miniRT.h>
#include <threadsRT.h>

static void	init_img_size(t_rt *rt)
{
	const uint16_t	height = rt->win->window_hght / (THREADS - 1);
	const uint16_t	remainder = rt->win->window_hght % (THREADS - 1);
	uint16_t		i;
//	render_width nog initializen????
	i = 0;
	rt->threads[i].height = height + remainder;
	rt->threads[i].width = rt->win->window_wdth;
	rt->threads[i].aspectr = (float)rt->win->window_wdth / (float)(height + remainder);
	rt->threads[i].start_y = 0;
	++i;
	while (i < THREADS - 1)
	{
		rt->threads[i].height = height;
		rt->threads[i].width = rt->win->window_wdth;
		rt->threads[i].aspectr = (float)rt->win->window_wdth / (float)height;
		rt->threads[i].start_y = rt->threads[i - 1].height + rt->threads[i - 1].start_y;
		++i;
	}
}

bool	img_multithreaded(t_rt *rt)
{
	uint16_t	i;
	uint16_t	last_height;

	i = 0;
	init_img_size(rt);
	last_height = 0;
	while (i < THREADS - 1)
	{
		rt->threads[i].img = mlx_new_image(rt->win->mlx, (int32_t)rt->threads[i].width, (int32_t)rt->threads[i].height);
		if (rt->threads[i].img == NULL)
		{
			return (img_deletion(rt, i), false);
		}
		rt->win->id = mlx_image_to_window(rt->win->mlx, rt->threads[i].img, 0, last_height);
		if (rt->win->id == -1) {
			return (img_deletion(rt, i), false);
		}
		rt->threads[i].pixels = (uint8_t *)rt->threads[i].img->pixels;
		last_height += rt->threads[i].height;
		++i;
	}
	return (true);
}

// Uiteindelijk vervangen door cleanup()
void	img_deletion(t_rt *rt, uint16_t img_amount)
{
	uint16_t	i;

	i = 0;
	while (i < img_amount)
	{
		mlx_delete_image(rt->win->mlx, rt->threads[i].img);
		++i;
	}
}
