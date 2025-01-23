#include "../include/minirt_param.h"

void	init_struct_m(t_minirt *m)
{
	ft_bzero(m, sizeof(t_minirt));
	m->scene.delta_time = 0.1f;
	m->scene.cam_fov_speed = FOV_SCROLL_SPEED;
	m->scene.cam_m_speed = CAM_MOVE_SPEED;
	m->scene.cam_r_speed = CAM_ROTATION_SPEED;
	m->scene.delta_time = EPSILON;
	m->win.resize = false;
	m->scene.render = true;
	m->win.aspectratio_w = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	m->win.rndr_hght = WIN_HEIGHT;
	m->win.rndr_wdth = WIN_WIDTH;
	m->win.res_ratio = 1.0f;
}
