#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>

//	Static Functions
static void	closing_cleanup_threads(t_rt *rt);
static void	scene_manipulate_keys(mlx_key_data_t keydata, t_rt *rt);

void	init_hooks(t_rt *rt)
{
	if (THREADS > 1)
		mlx_loop_hook(rt->win->mlx, (mlx_closefunc)loop_hook_threaded, rt);
	else
		mlx_loop_hook(rt->win->mlx, (mlx_closefunc)loop_hook, rt);
	mlx_key_hook(rt->win->mlx, (mlx_keyfunc)my_keyhook, rt);
	mlx_scroll_hook(rt->win->mlx, (mlx_cursorfunc)scroll_fov_hook, rt->scene);
	mlx_mouse_hook(rt->win->mlx, (mlx_mousefunc)mouse_hook, rt);
	mlx_close_hook(rt->win->mlx, (mlx_closefunc)closing_cleanup_threads, rt);
	reset_filename(rt->win);
}

void	my_keyhook(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ENTER || rt->win->file_creation == true)
		set_filename(keydata.key, rt->win, rt->scene);
	else if (keydata.key == MLX_KEY_K)
		rt->scene->selected_obj = &rt->scene->ambient;
	else if (keydata.key == MLX_KEY_P)
		print_obj_info(rt->scene);
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		closing_cleanup_threads(rt);
		mlx_close_window(rt->win->mlx);
	}
	else
		scene_manipulate_keys(keydata, rt);
}

void	brightness_keys(mlx_key_data_t keydata, t_rt *rt)
{
	float		upl;
	float		dol;
	const float	upa = rt->scene->ambient.a.ratio + 0.05F;
	const float	doa = rt->scene->ambient.a.ratio - 0.05F;

	if (keydata.key == MLX_KEY_EQUAL)
	{
		if (rt->scene->selected_obj != NULL && rt->scene->selected_obj->type == LIGHT)
		{
			upl = rt->scene->selected_obj->l.brightness + 0.05F;
			rt->scene->selected_obj->l.brightness = clamp(upl, 0.0F, 1.0F);
		}
		else
			rt->scene->ambient.a.ratio = clamp(upa, 0.0F, 1.0F);
		rt->scene->render = true;
	}
	else if (keydata.key == MLX_KEY_MINUS)
	{
		if (rt->scene->selected_obj != NULL && rt->scene->selected_obj->type == LIGHT)
		{
			dol = rt->scene->selected_obj->l.brightness - 0.05F;
			rt->scene->selected_obj->l.brightness = clamp(dol, 0.0F, 1.0F);
		}
		else
			rt->scene->ambient.a.ratio = clamp(doa, 0.0F, 1.0F);
		rt->scene->render = true;
	}
}

static void	scene_manipulate_keys(mlx_key_data_t keydata, t_rt *rt)
{
	if (handle_object_modification(keydata.key, rt->scene) == true)
		rt->scene->render = true;
	else if (keydata.key == MLX_KEY_L)
	{
		rt->scene->intersect_lights = !rt->scene->intersect_lights;
		rt->scene->render = true;
	}
	else if (keydata.key == MLX_KEY_RIGHT_SHIFT && THREADS > 1)
	{
		rt->scene->soft_shadows = !rt->scene->soft_shadows;
		rt->scene->render = true;
	}
	else
		brightness_keys(keydata, rt);
}

static void	closing_cleanup_threads(t_rt *rt)
{
	pthread_mutex_lock(rt->mtx + MTX_QUIT_ROUTINE);
	pthread_mutex_unlock(rt->mtx + MTX_RESYNC);
	rt->quit_routine = true;
	pthread_mutex_unlock(rt->mtx + MTX_QUIT_ROUTINE);
	pthread_mutex_lock(rt->mtx + MTX_STOPPED_THREADS);
	while (rt->stopped_threads < THREADS - 1)
	{
		pthread_cond_wait(&rt->cond, rt->mtx + MTX_STOPPED_THREADS);
	}
	pthread_mutex_unlock(rt->mtx + MTX_STOPPED_THREADS);
}
