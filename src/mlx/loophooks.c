#include <miniRT.h>
#include <RTmlx.h>
#include <scene.h>
#include <utils.h>

void	fov_hook(double xdelta, double ydelta, void *param)
{
	t_scene	*sc;

	(void)(xdelta);
	sc = (t_scene *)param;
	if (ydelta > 0 && sc->camera.camera.realtime_fov > 1.0f)
	{
		sc->camera.camera.realtime_fov -= 0.5f;
		sc->camera.camera.zvp_dist = 1.0f / tanf((sc->camera.camera.realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		printf("FOV: %.2f\n", sc->camera.camera.realtime_fov);
		return ;
	}
	if (ydelta < 0 && sc->camera.camera.realtime_fov < FOV_MAX)
	{
		sc->camera.camera.realtime_fov += 0.5f;
		sc->camera.camera.zvp_dist = 1.0f / tanf((sc->camera.camera.realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		printf("FOV: %.2f\n", sc->camera.camera.realtime_fov);
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

void	loop_hook(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	cam_hook(rt);
	if (rt->scene->render == true)
	{
		render_scene(rt, rt->scene);
		rt->scene->render = false;
	}
}
