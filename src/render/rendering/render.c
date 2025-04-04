#include <scene.h>
#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>
#include <threadsRT.h>

//	Normalized Device Coordinates
t_vec4	transform_ray_dir(t_vec4 ndc, t_vec4 cam_orient)
{
	const t_vec4	z_axis = vnorm(cam_orient);
	t_vec4			up;
	t_vec4			x_axis;
	t_vec4			y_axis;

	up = (t_vec4){0, 1, 0};
	if (fabsf(z_axis[X]) == 0.0F && fabsf(z_axis[Z]) == 0.0F)
	{
		if (z_axis[Y] > 0.0F)
			up = (t_vec4){0.0F, 0.0F, -1.0F};
		else
			up = (t_vec4){0.0F, 0.0F, 1.0F};
	}
	x_axis = vnorm(vcross(up, z_axis));
	y_axis = vcross(z_axis, x_axis);
	return (vnorm((t_vec4){
		x_axis[X] * ndc[X] + y_axis[X] * ndc[Y] + z_axis[X] * ndc[Z],
		x_axis[Y] * ndc[X] + y_axis[Y] * ndc[Y] + z_axis[Y] * ndc[Z],
		x_axis[Z] * ndc[X] + y_axis[Z] * ndc[Y] + z_axis[Z] * ndc[Z]
	}));
}

// Render the scene
void	render(t_rt *rt, t_window *w)
{
	float		ndc_x;
	float		ndc_y;
	t_ray		ray;
	t_axis2		axis;

	ray.origin = rt->scene->camera.coords;
	axis.y = 0;
	while (axis.y < w->rndr_hght)
	{
		axis.x = 0;
		while (axis.x < w->rndr_wdth)
		{
			ndc_x = (2.0F * ((axis.x + 0.5F) / (float)w->rndr_wdth) - 1.0F) * w->aspectrat;
			ndc_y = 1.0F - 2.0F * ((axis.y + 0.5F) / (float)w->rndr_hght);
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, rt->scene->camera.c.zvp_dist, 0.0F}, rt->scene->camera.c.orientation);
			scaled_res_set_pixel(w, axis.x, axis.y, trace_ray(rt->scene, ray));
			++axis.x;
		}
		++axis.y;
	}
}

// Render the scene (threaded)
bool	thread_render(t_thread *th, t_window *w)
{
	float	ndc_x;
	float	ndc_y;
	t_ray	ray;
	t_axis2	axis;

	axis.y = 0;
	ray.origin = th->scene->camera.coords;
	while (axis.y < w->rndr_hght)
	{
		if (check_bool(th->rt->mtx + MTX_RENDER, th->scene->render) == true
			|| check_bool(th->rt->mtx + MTX_QUIT_ROUTINE, th->rt->quit_routine) == true)
			return (true);
		axis.x = 0;
		while (axis.x < w->rndr_wdth)
		{
			ndc_x = (2.0F * ((axis.x + 0.5F) / (float)w->rndr_wdth) - 1.0F) * w->aspectrat;
			ndc_y = 1.0F - 2.0F * ((axis.y + 0.5F) / (float)w->rndr_hght);
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, th->scene->camera.c.zvp_dist, 0.0F}, th->scene->camera.c.orientation);
			set_pixel_multi(th, (uint16_t)w->res_ratio, axis, trace_ray(th->scene, ray));
			++axis.x;
		}
		++axis.y;
	}
	return (false);
}

void	thread_fast_render(t_thread *th, t_window *w)
{
	float	ndc_x;
	float	ndc_y;
	t_ray	ray;
	t_axis2	axis;

	axis.y = 0;
	ray.origin = th->scene->camera.coords;
	while (axis.y < w->rndr_hght)
	{
		axis.x = 0;
		while (axis.x < w->rndr_wdth)
		{
			ndc_x = (2.0F * ((axis.x + 0.5F) / (float)w->rndr_wdth) - 1.0F) * w->aspectrat;
			ndc_y = 1.0F - 2.0F * ((axis.y + 0.5F) / (float)w->rndr_hght);
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, th->scene->camera.c.zvp_dist, 0.0F}, th->scene->camera.c.orientation);
			set_pixel_multi(th, (uint16_t)w->res_ratio, axis, trace_ray(th->scene, ray));
			++axis.x;
		}
		++axis.y;
	}
}
