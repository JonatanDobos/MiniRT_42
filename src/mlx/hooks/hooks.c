#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>

//	Static Functions
static void	closing_cleanup_threads(t_rt *rt);

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
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_P)
			print_obj_info(rt->scene);
		if (keydata.key == MLX_KEY_ENTER || rt->win->file_creation == true)
			set_filename(keydata.key, rt->win, rt->scene);
		else if (keydata.key == MLX_KEY_ESCAPE)
		{
			closing_cleanup_threads(rt);
			mlx_close_window(rt->win->mlx);
		}
		else if (keydata.key == MLX_KEY_K)
			rt->scene->selected_obj = &rt->scene->ambient;
		else if (handle_object_modification(keydata.key, rt->scene) == true)
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
	}
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
