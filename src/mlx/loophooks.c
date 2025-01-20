#include <miniRT.h>
#include <RTmlx.h>

void	fov_hook(double xdelta, double ydelta, void *param)
{
	t_scene	*sc;

	(void)(xdelta);
	sc = (t_scene *)param;
	if (ydelta > 0 && sc->realtime_fov > 1.0f)
	{
		sc->realtime_fov -= 0.5f;
		sc->z_dist = 1.0f / tanf((sc->realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		printf("FOV: %.2f\n", sc->realtime_fov);
		return ;
	}
	if (ydelta < 0 && sc->realtime_fov < FOV_MAX)
	{
		sc->realtime_fov += 0.5f;
		sc->z_dist = 1.0f / tanf((sc->realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		printf("FOV: %.2f\n", sc->realtime_fov);
		return ;
	}
}

void	cam_hook(t_minirt *m)
{
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_W))
		cam_move_forw(&m->scene);
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_S))
		cam_move_backw(&m->scene);
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_D))
		cam_move_right(&m->scene);
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_A))
		cam_move_left(&m->scene);
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_SPACE))
		cam_move_up(&m->scene);
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_LEFT_SHIFT))
		cam_move_down(&m->scene);
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_LEFT))
		cam_rotate_left(&m->scene);
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_RIGHT))
		cam_rotate_right(&m->scene);
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_UP))
		cam_rotate_up(&m->scene);
	if (mlx_is_key_down(m->win.mlx, MLX_KEY_DOWN))
		cam_rotate_down(&m->scene);
}

void	loop_hook(void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	cam_hook(m);
	if (m->scene.render == true)
	{
		render(m);
		m->scene.render = false;
	}
}
