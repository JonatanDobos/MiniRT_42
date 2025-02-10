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

void	render_manager_thread(t_rt *rt)
{
	pthread_mutex_lock(rt->mtx + MTX_RENDER);
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
	pthread_mutex_unlock(rt->mtx + MTX_RENDER);
}

void	render_upscale_thread(t_thread *th)
{
	pthread_mutex_lock(th->rt->mtx + MTX_RENDER);
	th->rend_height = (float)th->height / th->rt->win->res_ratio;
	th->rend_width = (float)th->width / th->rt->win->res_ratio;
	pthread_mutex_unlock(th->rt->mtx + MTX_RENDER);
}
