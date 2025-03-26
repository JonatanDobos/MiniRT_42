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
	printf("Window Height: %u, Window Width: %u, Threads: %d\n", 
		rt->win->window_hght, rt->win->window_wdth, THREADS);
	i = 0;
	rt->threads[i].img_height = height + remainder;
	rt->threads[i].img_width = rt->win->window_wdth;
	// rt->threads[i].aspectr = (float)rt->win->window_wdth / (float)(height + remainder);
	rt->threads[i].start_y = 0;
	rt->threads[i].rdr_height = rt->threads[i].img_height / (uint16_t)(rt->win->res_ratio);
	printf("Thread %hu: img_height=%hu, img_width=%hu, start_y=%hu, rdr_height=%hu\n",
		i, rt->threads[i].img_height, rt->threads[i].img_width, rt->threads[i].start_y, rt->threads[i].rdr_height);
	// ++i;
	// while (i < THREADS - 1)
	// {
	// 	rt->threads[i].img_height = height;
	// 	rt->threads[i].img_width = rt->win->window_wdth;
	// 	// rt->threads[i].aspectr = (float)rt->win->window_wdth / (float)height;
	// 	rt->threads[i].start_y = rt->threads[i - 1].img_height / (uint16_t)(rt->win->res_ratio) + rt->threads[i - 1].start_y;
	// 	rt->threads[i].rdr_height = rt->threads[i].img_height / (uint16_t)(rt->win->res_ratio) + rt->threads[i].start_y;
	// 	printf("Thread %hu: img_height=%hu, img_width=%hu, start_y=%hu, rdr_height=%hu\n",
	// 	i, rt->threads[i].img_height, rt->threads[i].img_width, rt->threads[i].start_y, rt->threads[i].rdr_height);
	// 	++i;
	// }
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
		rt->threads[i].img = mlx_new_image(rt->win->mlx, (int32_t)rt->threads[i].img_width, (int32_t)rt->threads[i].img_height);
		if (rt->threads[i].img == NULL)
		{
			return (img_deletion(rt, i), false);
		}
		rt->win->id = mlx_image_to_window(rt->win->mlx, rt->threads[i].img, 0, last_height);
		if (rt->win->id == -1)
		{
			return (img_deletion(rt, i), false);
		}
		rt->threads[i].pixels_mlx = (uint8_t *)rt->threads[i].img->pixels;
		rt->threads[i].pixels_own = (uint8_t *)malloc(sizeof(uint8_t) * (rt->threads[i].img_width * rt->threads[i].img_height * 4));
		if (rt->threads[i].pixels_own == NULL)
			return (img_deletion(rt, i), false);
		last_height += rt->threads[i].img_height;
		rt->threads[i].pixels = rt->threads[i].pixels_own;
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
