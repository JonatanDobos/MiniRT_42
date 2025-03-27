#include <scene.h>
#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>
#include <utils.h>

void	render_manager(t_rt *rt)
{
	if (rt->scene->render == true)
	{
		rt->win->res_ratio = RES_R_LOW;
		rt->scene->render_ongoing = true;
		mlx_set_window_title(rt->win->mlx, "Rendering miniRT");
	}
	else if (rt->win->res_ratio > RES_R_FULL)
	{
		rt->win->res_ratio = clamp(rt->win->res_ratio - RES_STEP_SIZE, RES_R_FULL, RES_R_LOW);
	}
	else
	{
		rt->scene->render_ongoing = false;
		mlx_set_window_title(rt->win->mlx, "miniRT");
	}
	rt->win->rndr_hght = (float)rt->win->mlx->height / rt->win->res_ratio;
	rt->win->rndr_wdth = (float)rt->win->mlx->width / rt->win->res_ratio;
	render(rt);
}

static void	img_size(t_rt *rt)
{
	uint16_t	i;

	i = 0;
	rt->threads[i].rdr_height = rt->threads[i].img_height / (uint16_t)(rt->win->res_ratio);
	// printf("[%d] start_y: %hu, rdr_height: %hu\n", i, rt->threads[i].start_y, rt->threads[i].rdr_height);
	++i;
	while (i < THREADS - 1)
	{
		rt->threads[i].start_y = rt->threads[i - 1].img_height / (uint16_t)(rt->win->res_ratio) + rt->threads[i - 1].start_y;
		rt->threads[i].rdr_height = rt->threads[i].img_height / (uint16_t)(rt->win->res_ratio) + rt->threads[i].start_y;
		// printf("[%d] start_y: %hu, rdr_height: %hu\n", i, rt->threads[i].start_y, rt->threads[i].rdr_height);
		++i;
	}
}

void	render_manager_thread(t_rt *rt)
{
	if (rt->scene->render == true)
	{
		if (rt->win->res_ratio == RES_R_LOW)
			return ;
		rt->win->res_ratio = RES_R_LOW;
		rt->scene->render_ongoing = true;
		mlx_set_window_title(rt->win->mlx, "Rendering miniRT");
	}
	else if (rt->win->res_ratio > RES_R_FULL)
	{
		rt->win->res_ratio = clamp(rt->win->res_ratio - RES_STEP_SIZE, RES_R_FULL, RES_R_LOW);
	}
	else
	{
		rt->scene->render_ongoing = false;
		mlx_set_window_title(rt->win->mlx, "miniRT");
	}
	rt->win->rndr_hght = (float)rt->win->mlx->height / rt->win->res_ratio;
	rt->win->rndr_wdth = (float)rt->win->mlx->width / rt->win->res_ratio;
	img_size(rt);
}
