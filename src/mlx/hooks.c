#include <RTmlx.h>
#include <scene.h>
#include <utils.h>
#include <mathRT.h>
#include <render.h>
#include <debug.h>

void	my_keyhook(mlx_key_data_t keydata, t_rt *rt)
{
	bool	pressed_key = (keydata.action == MLX_PRESS);

	if (pressed_key == true)
	{
		if (handle_object_modification(keydata.key, rt->scene) == true)
		{
			rt->scene->render = true;
			return ;
		}
		if (keydata.key == MLX_KEY_1)
			print_camera(rt->scene->camera);
		if (keydata.key == MLX_KEY_EQUAL)
			rt->scene->render = res_upscale(rt->win);
		else if (keydata.key == MLX_KEY_MINUS)
			rt->scene->render = res_downscale(rt->win);
		else if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(rt->win->mlx);
	}
}

void	init_hooks(t_rt *rt)
{
	mlx_key_hook(rt->win->mlx, (mlx_keyfunc)my_keyhook, rt);
	mlx_loop_hook(rt->win->mlx, (mlx_closefunc)loop_hook, rt);
	mlx_mouse_hook(rt->win->mlx, (mlx_mousefunc)mouse_hook, rt);
	mlx_scroll_hook(rt->win->mlx, (mlx_cursorfunc)fov_hook, rt->scene);
}

void	fov_hook(double xdelta, double ydelta, t_scene *sc)
{
	(void)(xdelta);
	if (ydelta > 0 && sc->camera.c.realtime_fov > 0.1f)
	{
		sc->camera.c.realtime_fov = clamp(sc->camera.c.realtime_fov - sc->cam_fov_speed, 0.0f, 180.0f);
		sc->camera.c.zvp_dist = 1.0f / tanf((sc->camera.c.realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		printf("\033[0;34m FOV DOWN: %.2f\033[0m\n", sc->camera.c.realtime_fov);
		return ;
	}
	if (ydelta < 0 && sc->camera.c.realtime_fov < FOV_MAX)
	{
		sc->camera.c.realtime_fov = clamp(sc->camera.c.realtime_fov + sc->cam_fov_speed, 0.0f, 180.0f);
		sc->camera.c.zvp_dist = 1.0f / tanf((sc->camera.c.realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		printf("\033[0;34m FOV UP: %.2f\033[0m\n", sc->camera.c.realtime_fov);
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
