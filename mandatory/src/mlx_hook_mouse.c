#include "../include/minirt_param.h"

void	cursor_cam_switch(t_minirt *m, bool state)
{
	if (state == true)
	{
		mlx_set_cursor_mode(m->win.mlx, MLX_MOUSE_HIDDEN);
		m->win.mouse_pos_re_init = true;
		printf("\033[0;33m cursor cam ON\033[0m\n");
	}
	else
	{
		mlx_set_cursor_mode(m->win.mlx, MLX_MOUSE_NORMAL);
		mlx_set_mouse_pos(m->win.mlx, m->win.mlx->width / 2, m->win.mlx->height / 2);
		printf("\033[0;33m cursor cam OFF\033[0m\n");
	}
	m->win.mouse_integration = state;
}

void	mouse_hook(
	mouse_key_t but, action_t act, modifier_key_t mods, void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;

	if (but == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS)
		cursor_cam_switch(m, switch_bool(&m->win.mouse_integration));
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

void	cam_cursor_move(t_int x, t_int y, t_minirt *m)
{
	static double	prev_x = WIN_WIDTH / 2;
	static double	prev_y = WIN_HEIGHT / 2;
	double			delta_x;
	double			delta_y;

	mlx_get_mouse_pos(m->win.mlx, &x, &y);
	if (m->win.mouse_pos_re_init == true)
	{
		prev_x = (double)x;
		prev_y = (double)y;
		m->win.mouse_pos_re_init = false;
	}
	delta_x = (double)x - prev_x;
	delta_y = (double)y - prev_y;
	prev_x = (double)x;
	prev_y = (double)y;
	if (delta_x == 0.0 && delta_y == 0.0)
		return ;
	if (!cursor_inboud(m->win.mlx))
	{
		printf("\033[0;31m cursor out of bounds\033[0m\n");
		cursor_cam_switch(m, false);
		return ;
	}
	// Rotate camera orientation (yaw and pitch)
	m->scene.cam.orient = vec_rotate(m->scene.cam.orient, (t_vec4){0, 1, 0}, delta_x * m->scene.cam_sens);

	t_vec4 right = vec_cross((t_vec4){0, 1, 0}, m->scene.cam.orient);
	if (vec_len(right) < 1e-6)
	{ // Avoid zero-length right vector
		right = (t_vec4){1, 0, 0};
	}
	right = vec_normalize(right);
	m->scene.cam.orient = vec_rotate(m->scene.cam.orient, right, delta_y * m->scene.cam_sens);

	// Clamp pitch to avoid flipping
	if (fabs(m->scene.cam.orient[Y]) > 0.99)
	{
		m->scene.cam.orient[Y] = (m->scene.cam.orient[Y] > 0 ? 0.99 : -0.99);
	}
	m->scene.cam.orient = vec_normalize(m->scene.cam.orient);

	// Mark the scene for re-rendering
	m->scene.render = true;
}
