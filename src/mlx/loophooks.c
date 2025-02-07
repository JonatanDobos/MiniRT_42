#include <RTmlx.h>
#include <scene.h>
#include <utils.h>
#include <mathRT.h>
#include <render.h>

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

void	cam_hook(t_rt *rt)
{
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_W))
		cam_move_forw(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_S))
		cam_move_backw(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_D))
		cam_move_right(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_A))
		cam_move_left(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_SPACE))
		cam_move_up(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_LEFT_SHIFT))
		cam_move_down(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_LEFT))
		cam_rotate_left(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_RIGHT))
		cam_rotate_right(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_UP))
		cam_rotate_up(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_DOWN))
		cam_rotate_down(rt->scene);
}

// void	obj_rotate_up(t_scene *sc)
// {
// 	t_vec4 right = vcross(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F});
// 	sc->camera.c.orientation = vnorm(vrotate(sc->camera.c.orientation, right, sc->cam_r_speed));
// 	sc->render = true;
// }

// void	obj_rotate_down(t_scene *sc)
// {
// 	t_vec4 right = vcross(sc->selected_obj.orientation, (t_vec4){0.0F, 1.0F, 0.0F});
// 	sc->camera.c.orientation = vnorm(vrotate(sc->camera.c.orientation, right, -sc->cam_r_speed));
// 	sc->render = true;
// }

// void	obj_rotate_left(t_scene *sc)
// {
// 	sc->camera.c.orientation = vnorm(vrotate(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F}, -sc->cam_r_speed));
// 	sc->render = true;
// }

// void	obj_rotate_right(t_scene *sc)
// {
// 	sc->camera.c.orientation = vnorm(vrotate(sc->camera.c.orientation, (t_vec4){0.0F, 1.0F, 0.0F}, sc->cam_r_speed));
// 	sc->render = true;
// }

void	obj_hook(t_rt *rt)
{
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_W))
		rt->scene->render = obj_move_forw(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_S))
		rt->scene->render = obj_move_backw(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_A))
		rt->scene->render = obj_move_left(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_D))
		rt->scene->render = obj_move_right(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_SPACE))
		rt->scene->render = obj_move_up(rt->scene);
	if (mlx_is_key_down(rt->win->mlx, MLX_KEY_LEFT_SHIFT))
		rt->scene->render = obj_move_down(rt->scene);
	if (rt->scene->selected_obj->type != SPHERE)
	{
		// if (mlx_is_key_down(rt->win->mlx, MLX_KEY_LEFT))
		// 	obj_rotate_left(rt->scene);
		// if (mlx_is_key_down(rt->win->mlx, MLX_KEY_RIGHT))
		// 	obj_rotate_right(rt->scene);
		// if (mlx_is_key_down(rt->win->mlx, MLX_KEY_UP))
		// 	obj_rotate_up(rt->scene);
		// if (mlx_is_key_down(rt->win->mlx, MLX_KEY_DOWN))
		// 	obj_rotate_down(rt->scene);
	}
}

void	movement(t_rt *rt)
{
	if (rt->scene->selected_obj == NULL)
	{
		cam_hook(rt);
	}
	else
	{
		obj_hook(rt);
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
		time = 0.01;// testing!
		rt->scene->cam_fov_speed = FOV_SCROLL_SPEED * time;
		rt->scene->cam_m_speed = CAM_MOVE_SPEED * time;
		rt->scene->cam_r_speed = CAM_ROTATION_SPEED * time;
		rt->scene->render = false;
	}
}
