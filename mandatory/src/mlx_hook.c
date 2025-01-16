#include "../include/minirt_param.h"

static void	close_mlx(void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	exit_clean(m, errset(ERTRN));
}

static void	key_mlx(mlx_key_data_t key, void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	if (key.key == MLX_KEY_ESCAPE)
		return (close_mlx(m));
}

static void	resize_mlx(int32_t nhght, int32_t nwdth, void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	if (mlx_resize_image(m->win.img, nwdth, nhght) == false)
		exit_clean(m, perrmlx("resize_mlx", mlx_errno));
	m->win.pixels = m->win.img->pixels;
	m->win.ratio_w = (float)nwdth / (float)nhght;
	if ((t_uin16)nhght < m->win.rndr_hght)
		m->win.rndr_hght = nhght;
	m->win.rndr_wdth = (float)m->win.rndr_hght * m->win.ratio_w;
}

void	fov_hook(double xdelta, double ydelta, void *param)
{
	t_scene	*sc;

	(void)(xdelta);
	sc = (t_scene *)param;
	if (ydelta > 0 && sc->realtime_fov < FOV_MAX)
	{
		sc->realtime_fov += 0.5f;
		sc->z_dist = 1.0f / tanf((sc->realtime_fov * M_PI / 180.0f) / 2.0f);
		return ;
	}
	if (ydelta < 0 && sc->realtime_fov > 1)
	{
		sc->realtime_fov -= 0.5f;
		sc->z_dist = 1.0f / tanf((sc->realtime_fov * M_PI / 180.0f) / 2.0f);
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

void	init_hooks(t_minirt *m)
{
	mlx_close_hook(m->win.mlx, close_mlx, m);
	mlx_key_hook(m->win.mlx, key_mlx, m);
	mlx_resize_hook(m->win.mlx, resize_mlx, m);
	mlx_loop_hook(m->win.mlx, loop_hook, m);
	mlx_scroll_hook(m->win.mlx, fov_hook, &m->scene);
}
