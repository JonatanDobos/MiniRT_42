#include <scene.h>
#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>
#include <threadsRT.h>

t_vec4	transform_ray_dir(t_vec4 ndc_dir, t_vec4 cam_orient)
{
	// Normalize the camera orientation vector (forward direction)
	t_vec4	z_axis = vnorm(cam_orient);

	// Create an "up" vector (default is Y-axis in world space)
	t_vec4	up = {0, 1, 0};
	if (fabsf(z_axis[X]) == 0.0F && fabsf(z_axis[Z]) == 0.0F) // Handle edge case where cam_orient is vertical
		up = (z_axis[Y] > 0.0F) ? (t_vec4){0.0F, 0.0F, -1.0F} : (t_vec4){0.0F, 0.0F, 1.0F};

	// Calculate the right vector (x-axis of the camera)
	t_vec4	x_axis = vnorm(vcross(up, z_axis));

	// Calculate the up vector (y-axis of the camera, perpendicular to both)
	t_vec4	y_axis = vcross(z_axis, x_axis);

	// Apply the rotation matrix to the direction vector
	t_vec4 world_dir = {
		x_axis[X] * ndc_dir[X] + y_axis[X] * ndc_dir[Y] + z_axis[X] * ndc_dir[Z],
		x_axis[Y] * ndc_dir[X] + y_axis[Y] * ndc_dir[Y] + z_axis[Y] * ndc_dir[Z],
		x_axis[Z] * ndc_dir[X] + y_axis[Z] * ndc_dir[Y] + z_axis[Z] * ndc_dir[Z]
	};
	return (vnorm(world_dir));
}

// Render the scene
void	render(t_rt *rt)
{
	uint16_t	y;
	uint16_t	x;
	t_ray		ray;
	float		ndc_x;
	float		ndc_y;

	ray.origin = rt->scene->camera.coords;
	y = 0;
	while (y < rt->win->rndr_hght)
	{
		x = 0;
		while (x < rt->win->rndr_wdth)
		{
			ndc_x = (2.0F * ((x + 0.5F) / (float)rt->win->rndr_wdth) - 1.0F) * rt->win->aspectrat;
			ndc_y = 1.0F - 2.0F * ((y + 0.5F) / (float)rt->win->rndr_hght);
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, rt->scene->camera.c.zvp_dist, 0.0F}, rt->scene->camera.c.orientation);
			scaled_res_set_pixel(rt->win, x, y, trace_ray(rt->scene, ray));
			++x;
		}
		++y;
	}
}

// Render the scene (threaded)
bool	thread_render(t_thread *th, uint16_t y_rend)
{
	uint16_t		x;
	t_ray			ray;
	float			ndc_x;
	float			ndc_y;

	ray.origin = th->scene->camera.coords;
	while (y_rend < th->win->rndr_hght)
	{
		if (check_bool(th->rt->mtx + MTX_RENDER, th->scene->render) == true
			|| check_bool(th->rt->mtx + MTX_QUIT_ROUTINE, th->rt->quit_routine) == true)
			return (true);
		x = 0;
		while (x < th->win->rndr_wdth)
		{
			ndc_x = (2.0F * ((x + 0.5F) / (float)th->win->rndr_wdth) - 1.0F) * th->rt->win->aspectrat;
			ndc_y = 1.0F - 2.0F * ((y_rend + 0.5F) / (float)th->win->rndr_hght);
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, th->scene->camera.c.zvp_dist, 0.0F}, th->scene->camera.c.orientation);
			set_pixel_multi(th, (uint16_t)th->win->res_ratio, (t_axis2){x, y_rend}, trace_ray(th->scene, ray));
			++x;
		}
		++y_rend;
	}
	return (false);
}

void	thread_fast_render(t_thread *th, uint16_t y_rend)
{
	uint16_t		x;
	t_ray			ray;
	float			ndc_x;
	float			ndc_y;

	ray.origin = th->scene->camera.coords;
	while (y_rend < th->win->rndr_hght)
	{
		x = 0;
		while (x < th->win->rndr_wdth)
		{
			ndc_x = (2.0F * ((x + 0.5F) / (float)th->win->rndr_wdth) - 1.0F) * th->rt->win->aspectrat;
			ndc_y = 1.0F - 2.0F * ((y_rend + 0.5F) / (float)th->win->rndr_hght);
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, th->scene->camera.c.zvp_dist, 0.0F}, th->scene->camera.c.orientation);
			set_pixel_multi(th, (uint16_t)th->win->res_ratio, (t_axis2){x, y_rend}, trace_ray(th->scene, ray));
			++x;
		}
		++y_rend;
	}
}
