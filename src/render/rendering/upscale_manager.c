#include <scene.h>
#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>

void	upscale_manager(t_rt *rt)
{
	if (rt->scene->render == true)
	{
		rt->win->res_ratio = rt->win->res_r_start;
		rt->scene->render_ongoing = true;
		mlx_set_window_title(rt->win->mlx, "Rendering miniRT");
	}
	else if (rt->win->res_ratio > RES_R_FULL)
	{
		rt->win->res_ratio = intclamp( \
		rt->win->res_ratio - RES_STEP_SIZE, RES_R_FULL, rt->win->res_r_start);
	}
	else
	{
		rt->scene->render_ongoing = false;
		mlx_set_window_title(rt->win->mlx, "miniRT");
	}
	rt->win->rndr_hght = (float)rt->win->mlx->height / rt->win->res_ratio;
	rt->win->rndr_wdth = (float)rt->win->mlx->width / rt->win->res_ratio;
	render(rt, rt->win);
}

void	upscale_manager_thread(t_rt *rt)
{
	if (rt->scene->render == true)
	{
		if (rt->win->res_ratio == rt->win->res_r_start)
			return ;
		rt->win->res_ratio = rt->win->res_r_start;
		rt->scene->render_ongoing = true;
		rt->read_scene->shadow_sample_gridsize = 1;
		mlx_set_window_title(rt->win->mlx, "Rendering miniRT");
	}
	else if (rt->win->res_ratio > RES_R_FULL)
	{
		rt->win->res_ratio = intclamp( \
		rt->win->res_ratio - RES_STEP_SIZE, RES_R_FULL, rt->win->res_r_start);
		if (rt->win->res_ratio < rt->win->res_r_start - 2 \
			&& rt->read_scene->shadow_sample_gridsize < 4)
			rt->read_scene->shadow_sample_gridsize += rt->win->res_ratio % 2;
	}
	else
	{
		rt->scene->render_ongoing = false;
		rt->read_scene->shadow_sample_gridsize = 6;
	}
	rt->win->rndr_hght = (float)rt->win->mlx->height / rt->win->res_ratio;
	rt->win->rndr_wdth = (float)rt->win->mlx->width / rt->win->res_ratio;
}

void	set_starting_res_ratio(t_rt *rt, double delta_time)
{
	const double	error = delta_time - rt->win->target_time;
	const double	adjustment_factor = 10.0F;
	int				new_ratio;	

	new_ratio = rt->win->res_r_start * (1.0F + (error * adjustment_factor));
	rt->win->res_r_start = intclamp((int)new_ratio, 2, 30);
}
