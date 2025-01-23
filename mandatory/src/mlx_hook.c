#include "../include/minirt_param.h"

static void	close_mlx(void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	printf("\033[0;32mminiRT exitted\033[0m\n");
	exit_clean(m, errset(ERTRN));
}

static void	key_mlx(mlx_key_data_t key, void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	if (key.key == MLX_KEY_ESCAPE)
		return (close_mlx(m));
	if (key.key == MLX_KEY_EQUAL && key.action == MLX_PRESS)
		return (res_upscale(m));
	if (key.key == MLX_KEY_MINUS && key.action == MLX_PRESS)
		return (res_downscale(m));
	
}

static void	resize_mlx(int32_t nhght, int32_t nwdth, void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	if (mlx_resize_image(m->win.img, nwdth, nhght) == false)
		exit_clean(m, perrmlx("resize_mlx", mlx_errno));
	m->win.pixels = m->win.img->pixels;
	m->win.aspectratio_w = (float)nwdth / (float)nhght;
	m->win.rndr_hght = nhght;
	m->win.rndr_wdth = nwdth;
	m->win.res_ratio = 1.0f;
}

void	fov_hook(double xdelta, double ydelta, void *param)
{
	t_scene	*sc;

	(void)(xdelta);
	sc = (t_scene *)param;
	if (ydelta > 0 && sc->realtime_fov > 0.1f)
	{
		sc->realtime_fov = range(sc->realtime_fov - sc->cam_fov_speed, 0.1f, 180.0f);
		sc->z_dist = 1.0f / tanf((sc->realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		printf("\033[0;34m FOV DOWN: %.2f\033[0m\n", sc->realtime_fov);
		return ;
	}
	if (ydelta < 0 && sc->realtime_fov < FOV_MAX)
	{
		sc->realtime_fov = range(sc->realtime_fov + sc->cam_fov_speed, 0.1f, 180.0f);
		sc->z_dist = 1.0f / tanf((sc->realtime_fov * M_PI / 180.0f) / 2.0f);
		sc->render = true;
		printf("\033[0;34m FOV UP: %.2f\033[0m\n", sc->realtime_fov);
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
	double		time;

	m = (t_minirt *)param;
	cam_hook(m);
	if (m->scene.render == true)
	{
		time = mlx_get_time();
		render(m);
		time = mlx_get_time() - time;
		m->scene.delta_time = time;
		m->scene.cam_fov_speed = FOV_SCROLL_SPEED * time;
		m->scene.cam_m_speed = CAM_MOVE_SPEED * time;
		m->scene.cam_r_speed = CAM_ROTATION_SPEED * time;
		printf("\033[0;35m  > render %lf sec.\033[0m\n", time);
		m->scene.render = false;
	}
}

void	init_hooks(t_minirt *m)
{
	mlx_close_hook(m->win.mlx, close_mlx, m);
	mlx_key_hook(m->win.mlx, key_mlx, m);
	mlx_resize_hook(m->win.mlx, resize_mlx, m);
	mlx_loop_hook(m->win.mlx, loop_hook, m);
	mlx_scroll_hook(m->win.mlx, fov_hook, &m->scene);
}
