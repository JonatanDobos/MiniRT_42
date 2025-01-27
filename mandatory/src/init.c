#include "../include/minirt_param.h"

// Doesnt work (gets wrong monitor size)!
void	set_resolution(t_window *w)
{
	int32_t	wdth;
	int32_t	hght;

	mlx_get_monitor_size(0, &wdth, &hght);
	printf("Get monitor size: wdth:%d hght:%d\n", wdth, hght);
	if (!(wdth > 100 && hght > 100))
	{
		w->window_hght = WIN_HEIGHT_HD;
		w->window_wdth = WIN_WIDTH_HD;
		return ;
	}
	if ((float)(wdth / hght) > (float)(16 / 9 - 0.2) &&
		(float)(wdth / hght) < (float)(16 / 9 + 0.2))
	{
		if (wdth <= WIN_WIDTH_4K && wdth > WIN_WIDTH_2K)
		{
			w->window_hght = WIN_HEIGHT_2K;
			w->window_wdth = WIN_WIDTH_2K;
		}
		else if (wdth <= WIN_WIDTH_2K && wdth > WIN_WIDTH_FHD)
		{
			w->window_hght = WIN_HEIGHT_FHD;
			w->window_wdth = WIN_WIDTH_FHD;
		}
		else if (wdth <= WIN_WIDTH_FHD && wdth > WIN_WIDTH_HD)
		{
			w->window_hght = WIN_HEIGHT_HD;
			w->window_wdth = WIN_WIDTH_HD;
		}
		return ;
	}
	w->window_hght = hght - 10;
	w->window_wdth = wdth - 10;
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
