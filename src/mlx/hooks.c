#include <RTmlx.h>
#include <scene.h>
#include <utils.h>
#include <mathRT.h>
#include <render.h>
#include <debug.h>
#include <unistd.h>

bool	keybindings_used_in_loophook(const keys_t key)
{
	if (key == MLX_KEY_W || key == MLX_KEY_A || key == MLX_KEY_S || 
		key == MLX_KEY_D || key == MLX_KEY_UP || key == MLX_KEY_LEFT ||
		key == MLX_KEY_DOWN || key == MLX_KEY_RIGHT ||
		key == MLX_KEY_SPACE || key == MLX_KEY_LEFT_SHIFT)
	{
		return (true);
	}
	return (false);
}

void	mlx_closing_cleanup_threads(t_rt *rt)
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

bool	handle_custom_key(const keys_t key, t_rt *rt)
{
	if (handle_object_modification(key, rt->scene) == true)
		rt->scene->render = true;
	else if (key == MLX_KEY_1)
		print_camera(rt->scene->camera);
	else if (key == MLX_KEY_EQUAL)
		rt->scene->render = res_upscale(rt->win);
	else if (key == MLX_KEY_MINUS)
		rt->scene->render = res_downscale(rt->win);
	else if (key == MLX_KEY_ESCAPE) {
		mlx_closing_cleanup_threads(rt);
		mlx_close_window(rt->win->mlx);
	}
	else if (key == MLX_KEY_L)
	{
		rt->scene->intersect_lights = !rt->scene->intersect_lights;
		rt->scene->render = true;
	}
	else if (keybindings_used_in_loophook(key) == false)
		return (false);
	return (true);
}

void	my_keyhook(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.action == MLX_PRESS)
	{
		if (handle_custom_key(keydata.key, rt) == true)
		{
			rt->pressed_key = true;
		}
	}
	else if (keydata.action == MLX_RELEASE)
		rt->pressed_key = false;
}

void	init_hooks(t_rt *rt)
{
	if (THREADS > 1)
		mlx_loop_hook(rt->win->mlx, (mlx_closefunc)loop_hook_threaded, rt);
	else
		mlx_loop_hook(rt->win->mlx, (mlx_closefunc)loop_hook, rt);
	mlx_key_hook(rt->win->mlx, (mlx_keyfunc)my_keyhook, rt);
	mlx_mouse_hook(rt->win->mlx, (mlx_mousefunc)mouse_hook, rt);
	mlx_scroll_hook(rt->win->mlx, (mlx_cursorfunc)fov_hook, rt->scene);
	mlx_close_hook(rt->win->mlx, (mlx_closefunc)mlx_closing_cleanup_threads, rt);
}

void	fov_hook(double xdelta, double ydelta, t_scene *sc)
{
	(void)(xdelta);
	if (ydelta > 0 && sc->camera.c.realtime_fov > 0.1f)
	{
		sc->camera.c.realtime_fov = clamp(sc->camera.c.realtime_fov - sc->cam_fov_speed, 0.0f, 180.0f);
		sc->camera.c.zvp_dist = 1.0f / tanf((sc->camera.c.realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		// printf("\033[0;34m FOV DOWN: %.2f\033[0m\n", sc->camera.c.realtime_fov);
		return ;
	}
	if (ydelta < 0 && sc->camera.c.realtime_fov < FOV_MAX)
	{
		sc->camera.c.realtime_fov = clamp(sc->camera.c.realtime_fov + sc->cam_fov_speed, 0.0f, 180.0f);
		sc->camera.c.zvp_dist = 1.0f / tanf((sc->camera.c.realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		// printf("\033[0;34m FOV UP: %.2f\033[0m\n", sc->camera.c.realtime_fov);
		return ;
	}
}

void	loop_hook(t_rt *rt)
{
	double	time;

	time = mlx_get_time();
	movement(rt);
	if (rt->scene->render == true || rt->scene->render_ongoing == true)
	{
		render_manager(rt);
		time = mlx_get_time() - time;
		rt->win->delta_time = time;
		time = 0.01F;// maybe change to delta time!
		rt->scene->cam_fov_speed = FOV_SCROLL_SPEED * time;
		rt->scene->cam_m_speed = CAM_MOVE_SPEED * time;
		rt->scene->cam_r_speed = CAM_ROTATION_SPEED * time;
		rt->scene->render = false;
	}
}

void	loop_hook_threaded(t_rt *rt)
{
	double	time;

	time = mlx_get_time();
	movement(rt);

	pthread_mutex_lock(rt->mtx + MTX_DONE_RENDERING);
	if (rt->scene->render == true && rt->finished_rendering == THREADS - 1)
	{
		rt->pressed_key = false;
		pthread_mutex_lock(rt->mtx + MTX_SYNC);
		while (rt->finished_rendering != 0)
		{
			pthread_cond_wait(&rt->cond, rt->mtx + MTX_RESYNC);
		}
		// printf("huh %d\n", rt->finished_rendering);
		pthread_mutex_unlock(rt->mtx + MTX_RESYNC);
		pthread_mutex_lock(rt->mtx + MTX_RESYNC);
		pthread_mutex_unlock(rt->mtx + MTX_SYNC);
	}
	pthread_mutex_unlock(rt->mtx + MTX_DONE_RENDERING);


	pthread_mutex_lock(rt->mtx + MTX_RENDER);
	if (rt->scene->render == true || rt->scene->render_ongoing == true)
	{
		render_manager_thread(rt);
		time = mlx_get_time() - time;
		rt->win->delta_time = time;
		time = 0.01F;// maybe change to delta time!
		rt->scene->cam_fov_speed = FOV_SCROLL_SPEED * time;
		rt->scene->cam_m_speed = CAM_MOVE_SPEED * time;
		rt->scene->cam_r_speed = CAM_ROTATION_SPEED * time;
		rt->scene->render = false;
		// conditional lock?
		// pthread_cond_broadcast
		usleep(100);
	}
	pthread_mutex_unlock(rt->mtx + MTX_RENDER);
}
