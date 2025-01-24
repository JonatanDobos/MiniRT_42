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

void	mouse_hook(
	mouse_key_t but, action_t act, modifier_key_t mods, void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;

	if (but == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS)
	{
		switch_bool(&m->win.mouse_integration);
		if (m->win.mouse_integration == true)
		{
			mlx_set_cursor_mode(m->win.mlx, MLX_MOUSE_HIDDEN);
			// mlx_set_mouse_pos(m->win.mlx, m->win.mlx->width / 2, m->win.mlx->height / 2);
			printf("\033[0;33m cursor cam ON\033[0m\n");
		}
		else
		{
			mlx_set_cursor_mode(m->win.mlx, MLX_MOUSE_NORMAL);
			printf("\033[0;33m cursor cam OFF\033[0m\n");
		}
	}
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

void	cam_cursor_move(t_int x, t_int y, t_minirt *m)
{
	static double	prev_x = WIN_WIDTH / 2;
	static double	prev_y = WIN_HEIGHT / 2;
	double			delta_x;
	double			delta_y;

	// Get the mouse position (relative to the window)
	mlx_get_mouse_pos(m->win.mlx, &x, &y);

	// Calculate the movement delta
	delta_x = (double)x - prev_x;
	delta_y = (double)y - prev_y;
	prev_x = (double)x;
	prev_y = (double)y;
	printf("Mouse Position: x = %d, y = %d | Delta X: %.2f, Delta Y: %.2f\n",
		x, y, delta_x, delta_y);//t
	if (!cursor_inboud(m->win.mlx))
	{
		printf("IN Mouse Position: x = %d, y = %d | Delta X: %.2f, Delta Y: %.2f\n",
			x, y, delta_x, delta_y);//t
		mlx_set_mouse_pos(m->win.mlx, m->win.mlx->width / 2, m->win.mlx->height / 2);
		prev_x = m->win.mlx->width / 2;
		prev_y = m->win.mlx->height / 2;
		return ;
	}
	// Rotate camera orientation based on cursor movement
	// Horizontal movement (yaw)
	m->scene.cam.orient = vec_rotate(m->scene.cam.orient, (t_vec4){0, 1, 0}, delta_x * m->scene.cam_sens);

	// Vertical movement (pitch), limiting pitch to avoid flipping
	t_vec4	right = vec_normalize(vec_cross((t_vec4){0, 1, 0}, m->scene.cam.orient));
	m->scene.cam.orient = vec_rotate(m->scene.cam.orient, right, delta_y * m->scene.cam_sens);

	// Clamp the camera's orientation to prevent extreme pitch
	if (fabs(m->scene.cam.orient[Y]) > 0.99) // Avoid near-vertical orientations
		m->scene.cam.orient[Y] = (m->scene.cam.orient[Y] > 0 ? 0.99 : -0.99);
	m->scene.cam.orient = vec_normalize(m->scene.cam.orient);

	// Mark the scene for re-rendering
	m->scene.render = true;
}

void	cam_hook(t_minirt *m)
{
	if (m->win.mouse_integration == true)
		cam_cursor_move(0, 0, m);
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

// void	cursor_hook(double x, double y, void *param)
// {
// 	t_minirt		*m;
// 	static double	prev_x = 0;
// 	static double	prev_y = 0;
// 	const double	delta_x = x - prev_x;
// 	const double	delta_y = y - prev_y;

// 	m = (t_minirt *)param;
// 	if (m->win.mouse_integration == false)
// 		return ;
// 	mlx_get_mouse_pos(m->win.mlx, &x, &y);
// 	printf("Mouse Position: x = %d, y = %d | Delta X: %.2f, Delta Y: %.2f\n",
// 		x, y, delta_x, delta_y);//t
// 	if (cursor_inboud(m->win.mlx) == false)
// 	{
// 		puts("SET\n");
// 		mlx_set_mouse_pos(m->win.mlx, m->win.mlx->width / 2, m->win.mlx->height / 2);
// 		x = m->win.mlx->width / 2;
// 		y = m->win.mlx->height / 2;
// 	}
// 	prev_x = x;
// 	prev_y = y;
// 	// Rotate camera orientation based on cursor movement
// 	// Horizontal movement (yaw)
// 	m->scene.cam.orient = vec_rotate(m->scene.cam.orient, (t_vec4){0, 1, 0}, delta_x * m->scene.cam_sens);
// 	// Vertical movement (pitch), limiting pitch to avoid flipping
// 	t_vec4	right = vec_normalize(vec_cross((t_vec4){0, 1, 0}, m->scene.cam.orient));
// 	m->scene.cam.orient = vec_rotate(m->scene.cam.orient, right, delta_y * m->scene.cam_sens);
// 	// Clamp the camera's orientation to prevent extreme pitch
// 	if (fabs(m->scene.cam.orient[Y]) > 0.99) // Avoid near-vertical orientations
// 		m->scene.cam.orient[Y] = (m->scene.cam.orient[Y] > 0 ? 0.99 : -0.99);
// 	m->scene.cam.orient = vec_normalize(m->scene.cam.orient);
// 	// Mark the scene for re-rendering
// 	m->scene.render = true;
// }

void	loop_hook(void *param)
{
	t_minirt	*m;
	double		time;

	m = (t_minirt *)param;
	time = mlx_get_time();
	cam_hook(m);
	if (m->scene.render == true)
	{
		render(m);
		time = mlx_get_time() - time;
		m->scene.delta_time = time;
		m->scene.cam_fov_speed = FOV_SCROLL_SPEED * time;
		m->scene.cam_m_speed = CAM_MOVE_SPEED * time;
		m->scene.cam_r_speed = CAM_ROTATION_SPEED * time;
		m->scene.cam_sens = SENS * time;
		printf("\033[0;35m  > render %lf sec.\033[0m\n", time);
		m->scene.render = false;
	}
}

void	init_hooks(t_minirt *m)
{
	// mlx_cursor_hook(m->win.mlx, cursor_hook, m);
	mlx_mouse_hook(m->win.mlx, mouse_hook, m);
	mlx_close_hook(m->win.mlx, close_mlx, m);
	mlx_key_hook(m->win.mlx, key_mlx, m);
	mlx_resize_hook(m->win.mlx, resize_mlx, m);
	mlx_loop_hook(m->win.mlx, loop_hook, m);
	mlx_scroll_hook(m->win.mlx, fov_hook, &m->scene);
}
