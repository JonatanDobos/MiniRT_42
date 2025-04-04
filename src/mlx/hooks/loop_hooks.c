#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>

//	Static Functions
static void	render_updates(t_rt *rt);
static void	switch_pixelarray(t_rt *rt);

void	loop_hook(t_rt *rt)
{
	double	time;

	time = mlx_get_time();
	movement(rt);
	if (rt->scene->render == true || rt->scene->render_ongoing == true)
	{
		upscale_manager(rt);
		time = mlx_get_time() - time;
		if (rt->win->res_ratio == rt->win->res_r_start)
			rt->win->delta_time = time;
		rt->scene->cam_fov_speed = FOV_SCROLL_SPEED * rt->win->delta_time;
		rt->scene->cam_m_speed = CAM_MOVE_SPEED * rt->win->delta_time;
		rt->scene->cam_r_speed = CAM_ROTATION_SPEED * rt->win->delta_time;
		rt->scene->render = false;
	}
}

void	loop_hook_threaded(t_rt *rt)
{
	movement(rt);
	if (rt->scene->render == true)
		toggle_bool(rt->mtx + MTX_RENDER, &rt->read_scene->render, true);
	pthread_mutex_lock(rt->mtx + MTX_DONE_RENDERING);
	if ((rt->scene->render == true || rt->scene->render_ongoing == true)
		&& rt->finished_rendering == THREADS - 1)
	{
		pthread_mutex_lock(rt->mtx + MTX_SYNC);
		while (rt->finished_rendering != 0)
		{
			pthread_cond_wait(&rt->cond, rt->mtx + MTX_RESYNC);
		}
		toggle_bool(rt->mtx + MTX_RENDER, &rt->read_scene->render, false);
		pthread_mutex_unlock(rt->mtx + MTX_RESYNC);
		pthread_mutex_lock(rt->mtx + MTX_RESYNC);
		render_updates(rt);
		switch_pixelarray(rt);
		pthread_mutex_unlock(rt->mtx + MTX_SYNC);
	}
	pthread_mutex_unlock(rt->mtx + MTX_DONE_RENDERING);
}

static void	render_updates(t_rt *rt)
{
	if (rt->scene->render == true)
		cpy_scene(rt->scene, rt->read_scene);
	upscale_manager_thread(rt);
	rt->scene->cam_fov_speed = FOV_SCROLL_SPEED * rt->win->delta_time;
	rt->scene->cam_m_speed = CAM_MOVE_SPEED * rt->win->delta_time;
	rt->scene->cam_r_speed = CAM_ROTATION_SPEED * rt->win->delta_time;
	rt->scene->render = false;
}

static void	switch_pixelarray(t_rt *rt)
{
	if (rt->thread.pixels == rt->thread.pixels_mlx)
	{
		rt->thread.img->pixels = rt->thread.pixels_mlx;
		rt->thread.pixels = rt->thread.pixels_own;
	}
	else
	{
		rt->thread.img->pixels = rt->thread.pixels_own;
		rt->thread.pixels = rt->thread.pixels_mlx;
	}
}
