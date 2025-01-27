#include "../include/minirt_param.h"

// Doesnt work (gets wrong monitor size)!
void	set_resolution(t_window *w)
{
	int32_t	x;
	int32_t	y;

	mlx_get_monitor_size(0, &x, &y);
	printf("RESSET: x:%d y:%d\n");
	if (!(x > 100 && y > 100))
		return (w->window_hght = WIN_HEIGHT_HD, w->window_wdth = WIN_WIDTH_HD);
	if ((float)(x / y) > (float)(16 / 9 - 0.2) &&
		(float)(x / y) < (float)(16 / 9 + 0.2))
	{
		if (x <= WIN_WIDTH_4K && x > WIN_WIDTH_2K)
		{
			w->window_hght = WIN_HEIGHT_2K;
			w->window_wdth = WIN_WIDTH_2K;
		}
		else if (x <= WIN_WIDTH_2K && x > WIN_WIDTH_FHD)
		{
			w->window_hght = WIN_HEIGHT_FHD;
			w->window_wdth = WIN_WIDTH_FHD;
		}
		else if (x <= WIN_WIDTH_FHD && x > WIN_WIDTH_HD)
		{
			w->window_hght = WIN_HEIGHT_HD;
			w->window_wdth = WIN_WIDTH_HD;
		}
		return ;
	}
	w->window_hght = y - 10;
	w->window_wdth = x - 10;
}

void	init_struct_m(t_minirt *m)
{
	ft_bzero(m, sizeof(t_minirt));
	m->scene.delta_time = 0.1f;
	m->scene.cam_fov_speed = FOV_SCROLL_SPEED;
	m->scene.cam_m_speed = CAM_MOVE_SPEED;
	m->scene.cam_r_speed = CAM_ROTATION_SPEED;
	m->scene.delta_time = EPSILON;
	m->scene.render = true;
	set_resolution(&m->win);
	m->win.aspectratio_w = (float)m->win.window_wdth / (float)m->win.window_hght;
	m->win.rndr_hght = m->win.window_hght;
	m->win.rndr_wdth = m->win.window_wdth;
	m->win.res_ratio = 1.0f;
	m->win.resize = false;
}
