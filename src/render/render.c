#include <scene.h>
#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>

static t_vec4	transform_ray_dir(t_vec4 ndc_dir, t_vec4 cam_orient)
{
	// Normalize the camera orientation vector (forward direction)
	t_vec4	z_axis = vnorm(cam_orient);

	// Create an "up" vector (default is Y-axis in world space)
	t_vec4	up = {0, 1, 0};
	if (fabsf(z_axis[X]) == 0.0f && fabsf(z_axis[Z]) == 0.0f) // Handle edge case where cam_orient is vertical
		up = (z_axis[Y] > 0) ? (t_vec4){0, 0, -1} : (t_vec4){0, 0, 1};

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
	return vnorm(world_dir);
}

// Render the scene
void	render(t_rt *rt)
{
	uint16_t	y;
	uint16_t	x;
	t_ray		ray;
	float		ndc_x;
	float		ndc_y;

	y = 0;
	while (y < rt->win->rndr_hght)
	{
		x = 0;
		while (x < rt->win->rndr_wdth)
		{
			ndc_x = (2 * ((x + 0.5f) / (float)rt->win->rndr_wdth) - 1) * rt->win->aspectrat;
			ndc_y = 1 - 2 * ((y + 0.5f) / (float)rt->win->rndr_hght);
			ray.origin = rt->scene->camera.coords;
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, rt->scene->camera.c.zvp_dist, 0}, rt->scene->camera.c.orientation);
			scaled_res_set_pixel(rt->win, x, y, trace_ray(rt->scene, ray));
			++x;
		}
		++y;
	}
}
